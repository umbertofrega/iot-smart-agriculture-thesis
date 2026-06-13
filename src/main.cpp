#include "esp32-hal-gpio.h"
#include "io_pin_remap.h"
#include "pins_arduino.h"
#include <Arduino.h>
#include <network_manager.h>

void setup() {
  Serial.begin(115200);
  delay(2000);
  pinMode(LED_GREEN, OUTPUT);

  boolean cr = connectToWifi();

  if(cr){
    digitalWrite(LED_GREEN, LOW);
  } else {
    digitalWrite(LED_BLUE, LOW);
  }
}

void loop() {}
