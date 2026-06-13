#include <Arduino.h>
#include "network/network_manager.h"

NetworkManager networkManager;

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

  networkManager.mantainConnections();
}
