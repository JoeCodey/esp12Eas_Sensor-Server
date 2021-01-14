#include "ESPLibraryTools.h"
// ESPLibTool includes:-> ESP8266WebServer.h , ESP8266mDNS.h
#include "UDP_Communication.h"
#include "deviceServer.h"
#include <MemoryFree.h>
#include <Ticker.h> 



// #include <WiFiManager.h> // Unused library for saving network credentials in non-volitile memory

#define led_motion D4  // output pin for LED triggered on motion events 
#define motionSensor D2 // digital logic output of passive infrared sensor  
#define IP "192.168.2.68  " 
const char* ssid = "";
const char* password = "" ;
unsigned long inacitvityTime = 0 ; 
unsigned long referenceTime = 0 ; // time of last sensor event 
/** Global Vars **/ // TODO?: Move to json config file ? 

int motionFlag = 0 ; 
int pirState = LOW ; 
char packetBuffer[255]; //buffer to hold incoming packet
char  ReplyBuffer[] = "acknowledged";       // a string to send back
unsigned int UDPPort = 50000 ; // UDP port must match connection on receiving end 

// Instance of Ticker Class to monitor time without 

//ESP8266 device is now a webserver 
DeviceServer server(80);                                                                       
/** Class instances of UdpComm --> subclass of WiFiUDP from ESP8266 library **/ 
UdpComm udp(IP,UDPPort);

void testSleepFunction(){
  server.foo() ; 
}

void detectMotion(){
      String detect_event = " Motion Event Detected";
      String end_event = " Motion Event Ended";
      int mem = 0 ; 
      

    if (motionFlag == HIGH) {   
       referenceTime = millis() ; // motion detected -> reset time of latest event ; 
       mem = freeMemory() ; // Check free memory   
          // check if the input is HIGH
        digitalWrite(led_motion, LOW);  // turn LED ON
        if (pirState == LOW) {
        // we have just turned on
        Serial.println("\t--serial-- Motion detected!");
        
        udp.sendUDPpacket(detect_event += mem);
        // We only want to print on the output change, not state
        pirState = HIGH;
        }
    } else if( motionFlag == LOW ) { 
        inacitvityTime = millis() - referenceTime  ; 
        digitalWrite(led_motion, HIGH); // turn LED OFF
        if (pirState == HIGH){

        udp.sendUDPpacket(end_event); 
        Serial.println("\t--serial-- Motion ended!");

        // We only want to print on the output change, not state
        pirState = LOW;
        }
    }
}

void setup(void) {
  /* seting hardware pins */
  pinMode(led_motion, OUTPUT); // LED indicator for motion 
  pinMode(motionSensor,INPUT); // Motion sensor pin 
  digitalWrite(led_motion, HIGH); // motion LED -> OFF
  Serial.begin(115200); // baud rate for serial communication 
  
  WiFi.mode(WIFI_STA);
  
  WiFi.begin(ssid, password);
  // WiFi.softAP()

  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  // Connect and verify WiFi is connected 
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  udp.begin(UDPPort) ; // ----- Begin UDP 
  
  // if (MDNS.begin("motion")) {
  //   Serial.println("MDNS responder started");
  // }

  server.begin();
 
  Serial.println("HTTP server started");
  delay(2000);
  udp.sendUDPpacket("TESTING UDP CONNECTION");
  delay(2000);  
}

void loop(void) {
  motionFlag = digitalRead(motionSensor);
  if (inacitvityTime > 1000*30){
    /* no motion has been detected for 30 seconds,
     * entering deepsleep mode
     * motion sensor will trigger reset pin and wake device 
    */
    inacitvityTime = 0 ; 
    ESP.deepSleep(5e6);   
    //ESP.reset() ; 
  }
  detectMotion();
  server.handleClient();
//  MDNS.update(
}

