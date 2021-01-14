#ifndef UDP_COMMUNICATION_H
#define UDP_COMMUNICATION_H
/**
 * Sub class of WifiUDP from ESP8266WiFi library 
 * -> encapsulates functions for udp communication in this project
*/
#include <ESPLibraryTools.h> 

class UdpComm : public WiFiUDP 
{
public : 
    using WiFiUDP::WiFiUDP ; 

    UdpComm(const char *, unsigned int port);

    const char * IPaddr ; 
    uint16_t port ; 

    void sendUDPpacket( const String & motionEvent) ;
};


#endif  