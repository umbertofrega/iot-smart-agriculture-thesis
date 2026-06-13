#include <Arduino.h>
#include "network_manager.h"
#include "mqtt_manager.h"

NetworkManager networkManager;
MqttManager mqttManager;

void setup()
{
  Serial.begin(115200);
  delay(2000);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
  pinMode(LED_RED, OUTPUT);

  if (networkManager.connectToWifi())
  {
    digitalWrite(LED_GREEN, LOW);
  }

  if (mqttManager.connectToBroker())
  {
    digitalWrite(LED_BLUE, LOW);
  }
}

void loop()
{
  if (!networkManager.isConnected())
  {
    digitalWrite(LED_GREEN, HIGH);
  }

  if (!mqttManager.isConnected())
  {
    digitalWrite(LED_BLUE, HIGH);
    if (mqttManager.connectToBroker())

    {
      digitalWrite(LED_BLUE, LOW);
    }
  }

  mqttManager.loop();
}
