#include <PubSubClient.h>
#include <WiFi.h>
#include "secrets.h"

class MqttManager
{
private:
    WiFiClient wifiClient;
    PubSubClient mqttClient;

public:
    MqttManager() : mqttClient(wifiClient)
    {
        mqttClient.setServer(mqtt_broker, mqtt_port);
    }

    bool connectToBroker()
    {
        Serial.println("MQTT Connection Started");

        if (mqttClient.connect("esp32tesi"))
        {
            Serial.println("Connected to Broker Successfully");

            mqttClient.publish("esp32/connection", "Connected");
            return true;
        }

        Serial.println("Connection Failed");
        return false;
    }

    void loop()
    {
        mqttClient.loop();
    }

    bool isConnected()
    {
        return mqttClient.connected();
    }
};