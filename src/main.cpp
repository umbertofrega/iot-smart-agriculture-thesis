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

  float ph = sensorsManager.getPh();
  float temp = sensorsManager.getTemp();
  float hum = sensorsManager.getHumidity();

  data["ph"] = ph;
  data["temp"] = temp;
  data["humidity"] = hum;

  char buffer[256];

  serializeJson(data, buffer);

  serializeJsonPretty(data, Serial);

  if (ph > 6.5)
  {
    mixersManager.mixBasic();
  }
  else if (ph < 4)
  {
    mixersManager.mixAcidic();
  }

  if (networkManager.connect())
  {
    networkManager.publishSensors(buffer);

    networkManager.disconnect();
  }

  else
  {
    Serial.println("Error in connection, resuming deep sleep");
  }
}

void loop()
{
}