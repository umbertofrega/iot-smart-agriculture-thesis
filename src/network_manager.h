#include <WiFi.h>
#include <secrets.h>

class NetworkManager{
    public:
        boolean connectToWifi(){
            int tries = 20;

            WiFi.begin(ssid,passwd);
            Serial.println("Connecting to WiFi");

            while(WiFi.status() != WL_CONNECTED && tries > 0){
                tries--;
                delay(500);
            }
            
            if(WiFi.status() == WL_CONNECTED){
                Serial.print("Connection successful!");
                return true;
            } else {
                Serial.print("Connection failed");
                return false;
            }
        }

        boolean isConnected(){
            return WiFi.status() != WL_CONNECTED;
        }

};