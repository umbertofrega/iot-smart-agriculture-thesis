#include <Arduino.h>
#include "wifi_manager.h"
#include "mqtt_manager.h"

WifiManager wifiManager;
MqttManager mqttManager;

void setup()
{
  Serial.begin(115200);
  delay(2000);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
  pinMode(LED_RED, OUTPUT);
}

void loop()
{
  mantainConnections();
  mqttManager.loop();
}

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
}
