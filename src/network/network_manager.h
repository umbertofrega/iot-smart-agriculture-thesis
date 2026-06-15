#include "wifi_manager.h"
#include "mqtt_manager.h"

class NetworkManager
{
private:
    WifiManager wifiManager;
    MqttManager mqttManager;

public:
    boolean connect()
    {
        if (!wifiManager.isConnected())
        {
            digitalWrite(LED_BLUE, HIGH);

            if (wifiManager.connectToWifi())
            {
                digitalWrite(LED_BLUE, LOW);
            }
            else
            {
                return false;
            }
        }

        if (mqttManager.connectToBroker())
        {
            digitalWrite(LED_BLUE, HIGH);
            digitalWrite(LED_GREEN, LOW);
            mqttManager.loop();
            return true;
        }
        else
        {
            return false;
        }
    }

    void disconnect()
    {
        mqttManager.disconnect();
        wifiManager.disconnect();
    }

    void publishSensors(char *data)
    {

        mqttManager.publish(data);
    }
};