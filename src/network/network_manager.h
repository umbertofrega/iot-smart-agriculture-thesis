#include "wifi_manager.h"
#include "mqtt_manager.h"

class NetworkManager
{
private:
    WifiManager wifiManager;
    MqttManager mqttManager;

public:
    void mantainConnections()
    {
        if (!wifiManager.isConnected())
        {
            digitalWrite(LED_GREEN, HIGH);

            if (wifiManager.connectToWifi())
            {
                digitalWrite(LED_GREEN, LOW);
            }
            else
            {
                return;
            }
        }

        if (!mqttManager.isConnected())
        {
            digitalWrite(LED_BLUE, HIGH);
            if (mqttManager.connectToBroker())

            {
                digitalWrite(LED_BLUE, LOW);
            }
        }
        else
        {
            mqttManager.loop();
        }
    }
};