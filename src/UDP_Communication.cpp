#include "UDP_Communication.h"

UdpComm::UdpComm(const char * ip , unsigned int p) : 
    IPaddr(ip), port(p) {} 

void UdpComm::sendUDPpacket(const String& motionEvent){
  Serial.println("... Attempting to send packet " + motionEvent);
  this->beginPacket(IPaddr,port);
  char messageBuffer[255];
  motionEvent.toCharArray(messageBuffer,255);
  this->write(messageBuffer) ; 
  this->endPacket();
} 