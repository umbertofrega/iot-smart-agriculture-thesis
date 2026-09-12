#include <Arduino.h>
#include <esp_sleep.h>
#include <ArduinoJson.h>
#include "sensors/sensors_manager.h"
#include "network/network_manager.h"
#include "actuators/mixer_manager.h"

NetworkManager networkManager;
SensorsManager sensorsManager;
MixersManager mixersManager;

void setup()
{
  Serial.begin(115200);
  delay(2000);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
  pinMode(LED_RED, OUTPUT);

  JsonDocument data;

  float temp = 34;
  float ph = 5;
  float hum = 30;

  data["ph"] = ph;
  data["temp"] = temp;
  data["humidity"] = hum;

  char sensorsBuffer[256];

  char mixersBuffer[256];

  serializeJson(data, sensorsBuffer);

  serializeJsonPretty(data, Serial);

  data.clear();

  if (hum < 30)
  {
    data["irrigation"] = true;
    if (ph > 6.5)
    {
      mixersManager.mixBasic();
      data["mixed"] = "basic";
    }
    else if (ph < 4)
    {
      mixersManager.mixAcidic();
      data["mixed"] = "acid";
    }
    else
    {
      data["mixed"] = "didn't mix";
    }

    serializeJson(data, mixersBuffer);

    serializeJsonPretty(data, Serial);
  }

  if (networkManager.connect())
  {
    networkManager.publishSensors(sensorsBuffer);

    networkManager.publishMixers(mixersBuffer);

    networkManager.disconnect();
  }
}

void loop()
{
}