#include <Arduino.h>
#include <esp_sleep.h>
#include <ArduinoJson.h>
#include "network/network_manager.h"
#include "sensors/sensors_manager.h"
#include "actuators/mixer_manager.h"

NetworkManager networkManager;
SensorsManager sensorsManager;
// MixersManager mixersManager;

void onWakeUp()
{
  float pH = sensorsManager.getPh();
  float temp = sensorsManager.getTemp();
  JsonDocument data;

  data["pH"] = pH;
  data["Temperature"] = temp;

  if (pH > 7)
  {
    // mixersManager.mixBasic();
    data["BasicMixer"] = "ON";
  }
  else if (pH < 5.5)
  {
    // mixersManager.mixAcidic();
    data["AcidicMixer"] = "ON";
  }

  char buffer[256];

  serializeJson(data, buffer);

  serializeJsonPretty(data, Serial);
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

void setup()
{
  Serial.begin(115200);
  delay(2000);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
  pinMode(LED_RED, OUTPUT);

  // esp_sleep_enable_timer_wakeup(30 * 1000000ULL);

  onWakeUp();

  // esp_deep_sleep_start();
}

void loop()
{
}