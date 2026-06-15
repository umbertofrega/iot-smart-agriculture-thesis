#include <Arduino.h>
#include <esp_sleep.h>
#include "network/network_manager.h"

NetworkManager networkManager;

void setup()
{
  Serial.begin(115200);
  delay(2000);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
  pinMode(LED_RED, OUTPUT);

  esp_sleep_enable_timer_wakeup(30 * 1000000ULL);

  wake_up_operations();

  esp_deep_sleep_start();
}

void wake_up_operations()
{
  networkManager.connect();

    networkManager.disconnect();
}

void loop() {}