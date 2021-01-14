 #include "ESPLibraryTools.h"
#include <unity.h>



void test_light_sleep(void){
    WiFi.setSleepMode(WIFI_LIGHT_SLEEP);
    delay(500) ;

    WiFiSleepType sleepType =  WiFi.getSleepMode();
    TEST_ASSERT_EQUAL_INT(WIFI_LIGHT_SLEEP,sleepType) ; 
}

void test_modem_sleep(void){
    WiFi.setSleepMode(WIFI_MODEM_SLEEP);
    delay(500) ;

    WiFiSleepType sleepType =  WiFi.getSleepMode();
    TEST_ASSERT_EQUAL_INT(WIFI_MODEM_SLEEP,sleepType) ; 
} 