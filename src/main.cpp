#include <Arduino.h>
#include <esp_sleep.h>
#include <ArduinoJson.h>
#include "sensors/sensors_manager.h"
#include "network/network_manager.h"

NetworkManager networkManager;
SensorsManager sensorsManager;

void setup()
{
  Serial.begin(115200);
  delay(2000);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
  pinMode(LED_RED, OUTPUT);

  JsonDocument data;

  // float temp = sensorsManager.getTemp();
  // float ph = sensorsManager.getPh(temp);
}

void loop()
{
  Serial.println(sensorsManager.getHumidityPercentage());

  delay(2000);
}