#include <WiFi.h>
#include "secrets.h"

class NetworkManager{
    public:
        bool connectToWifi(){
            int tries = 20;

            WiFi.begin(ssid,passwd);
            Serial.println("Connecting to WiFi");

            while(WiFi.status() != WL_CONNECTED && tries > 0){
                tries--;
                delay(500);
            }
            
            if(WiFi.status() == WL_CONNECTED){
                Serial.println("Connection successful!");
                return true;
            } else {
                Serial.println("Connection failed");
                return false;
            }
        }

        bool isConnected(){
            return WiFi.status() == WL_CONNECTED;
        }
};