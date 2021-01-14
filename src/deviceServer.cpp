#include "deviceServer.h"

/**
 * DeviceServer Constructor 
 * - Call ESP8266Webserver (base classe) Construor 
 * - AND implement common http respones to routes
 * - e.g. server.on("/ping",[]{....}
 * **/
DeviceServer::DeviceServer(int port ) : ESP8266WebServer(port){
  routerFunc("/motion",[this]{
      send(200, "text/plain", 
      "hello from deviceSERVER! --Online and responding");
  });
  routerFunc("/inline",[this]{
      send(200, "text/plain", 
      "this works as well");
  });
}

void DeviceServer::foo(){
  //Dummy function for testing  
  Serial.println("hello from device server");
}

void DeviceServer::routerFunc(const Uri &route, THandlerFunction func){
  /** calls function BaseClass:: on(route,Thandler function) ,
  * which adds new function to be triggered by the server 
  * on a specified route. 
  **/
  this->on(route,func);
}

void DeviceServer::onNotFound(){
  ESP8266WebServer::onNotFound([this]{
        String message = "File Not Found\n\n";
        message += "URI: ";
        message += uri();
        message += "\nMethod: ";
        message += (method() == HTTP_GET) ? "GET" : "POST";
        message += "\nArguments: ";
        message += args()
        ;
        message += "\n";
        for (uint8_t i = 0; i < args(); i++) {
            message += " " + argName(i) + ": " + arg(i) + "\n";
        }
        send(404, "text/plain", message);\
     });
}
