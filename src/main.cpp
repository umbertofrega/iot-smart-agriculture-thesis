#include <Arduino.h>
#include "network_manager.h"

NetworkManager networkManager;

void setup() {
  Serial.begin(115200);
  delay(2000);
  pinMode(LED_GREEN, OUTPUT);


  if (networkManager.connectToWifi()){
    digitalWrite(LED_GREEN, LOW);
  } 
}

void loop() {}
