
#ifndef DEVICE_SERVER_H
#define DEVICE_SERVER_H

#include "ESPLibraryTools.h"

/**
 * Custom class DeviceServer inherits from ESP_Library
 *  - implements handle functions for http requests as methods to DeviceServer class
 *  - ThandlerFunction is a typedef for std::function<void(void)> as defined in ESP8266WebServer.h
 * 
 * **/

class DeviceServer : public ESP8266WebServer
{
public:
   using ESP8266WebServer::ESP8266WebServer ; 

   DeviceServer(int port);

     void foo()  ;
     void routerFunc(const Uri &route, THandlerFunction func); 
     void onNotFound(); 

};
#endif 

