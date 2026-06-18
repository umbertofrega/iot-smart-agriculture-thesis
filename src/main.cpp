#include <Arduino.h>
#include <esp_sleep.h>
#include "network/network_manager.h"
#include "sensors/sensors_manager.h"
#include "actuators/mixer_manager.h"

NetworkManager networkManager;
SensorsManager sensorsManager;
MixersManager mixersManager;

void onWakeUp()
{
  float pH = sensorsManager.getData();

  if (pH > 7.5f)
  {
    mixersManager.mixBasic();
  }
  else if (pH < 4)
  {
    mixersManager.mixAcidic();
  }

  if (networkManager.connect())
  {
    networkManager.publishSensors(data);

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