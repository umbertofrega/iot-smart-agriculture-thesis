#include <Arduino.h>
#include <esp_sleep.h>
#include <ArduinoJson.h>
#include "sensors/sensors_manager.h"
#include "network/network_manager.h"
#include "actuators/mixer_manager.h"
#include "actuators/sprinkler.h"

NetworkManager networkManager;
SensorsManager sensorsManager;
MixersManager mixersManager;
Sprinkler sprinkler;

const uint64_t TIME_TO_SLEEP_SEC = 60;

void setup()
{
  Serial.begin(115200);
  delay(2000);

  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
  pinMode(LED_RED, OUTPUT);

  esp_sleep_wakeup_cause_t cause = esp_sleep_get_wakeup_cause();
  if (cause == ESP_SLEEP_WAKEUP_TIMER)
  {
    Serial.println("\n[SISTEMA] Risveglio dal Deep Sleep.");
  }
  else
  {
    Serial.println("\n[SISTEMA] Avvio pulito o Reset.");
  }

  sensorsManager.beginAll();

  float temp = sensorsManager.getTemp();
  float ph = sensorsManager.getPh((int)temp);
  int hum = sensorsManager.getHumidityPercentage();

  Serial.printf("Letture -> Temp: %.2fC | pH: %.2f | Hum: %d%%\n", temp, ph, hum);

  JsonDocument data;
  data["ph"] = ph;
  data["temp"] = temp;
  data["humidity"] = hum;

  char sensorsBuffer[256];
  char mixersBuffer[256];

  serializeJson(data, sensorsBuffer);
  serializeJsonPretty(data, Serial);
  Serial.println();

  data.clear();

  if (hum < 30)
  {
    Serial.println("[ATTUATORI] Terreno secco. Calcolo mix...");
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

    sprinkler.start();
    Serial.println("Irrigazione avviata per 5 secondi...");

    delay(5000);

    sprinkler.stop();
    Serial.println("Irrigazione terminata.");

    serializeJson(data, mixersBuffer);
    serializeJsonPretty(data, Serial);
    Serial.println();

    Serial.println("[NETWORK] Connessione WiFi/MQTT in corso...");
    if (networkManager.connect())
    {
      networkManager.publishSensors(sensorsBuffer);
      networkManager.publishMixers(mixersBuffer);
      networkManager.disconnect();
      Serial.println("[NETWORK] Dati inviati. Disconnesso.");
    }
    else
    {
      Serial.println("[NETWORK] Impossibile connettersi.");
    }
  }
  else
  {
    Serial.println("[ATTUATORI] Umidità OK. Salto le pompe e il WiFi.");
  }

  Serial.printf("\n[SISTEMA] Vado in Deep Sleep per %llu secondi...\n", TIME_TO_SLEEP_SEC);
  esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP_SEC * 1000000ULL);
  Serial.flush();
  esp_deep_sleep_start();
}

void loop()
{
}