#include <Arduino.h>
#include <esp_sleep.h>
#include "network/network_manager.h"
#include "sensors/sensors_manager.h"

NetworkManager networkManager;
SensorsManager sensorsManager;

void setup()
{
  Serial.begin(115200);
  delay(2000);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
  pinMode(LED_RED, OUTPUT);

  esp_sleep_enable_timer_wakeup(30 * 1000000ULL);

  onWakeUp();

  esp_deep_sleep_start();
}

void onWakeUp()
{
  char *data = sensorsManager.getData();

  networkManager.connect();

  networkManager.publishSensors(data);

  networkManager.disconnect();
}

void loop() {}