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
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
  pinMode(LED_RED, OUTPUT);
  delay(2000);

  // 1. Controllo motivo del risveglio
  esp_sleep_wakeup_cause_t cause = esp_sleep_get_wakeup_cause();
  if (cause == ESP_SLEEP_WAKEUP_TIMER)
  {
    Serial.println("\n[SISTEMA] Risveglio dal Deep Sleep.");
  }
  else
  {
    Serial.println("\n[SISTEMA] Avvio pulito o Reset.");
  }

  // 2. Acquisizione dati Sensori
  sensorsManager.beginAll();
  int hum = sensorsManager.getHumidityPercentage();
  float temp = sensorsManager.getTemp();
  float ph = sensorsManager.getPh((int)temp);

  Serial.printf("Letture -> Temp: %.2fC | pH: %.2f | Hum: %d%%\n", temp, ph, hum);

  // 3. Preparazione e Invio TELEMETRIA (Eseguito SEMPRE)
  JsonDocument data;
  data["ph"] = ph;
  data["temp"] = temp;
  data["humidity"] = hum;

  char sensorsBuffer[256];
  serializeJson(data, sensorsBuffer);

  Serial.println("[TELEMETRIA SENSORI] Pronta per la dashboard:");
  serializeJsonPretty(data, Serial);
  Serial.println();

  // 4. Logica Attuatori e Irrigazione
  data.clear();
  char mixersBuffer[256];

  if (hum < 30)
  {
    Serial.println("[ATTUATORI] Terreno secco. Calcolo mix e avvio irrigazione...");
    data["irrigation"] = true;

    if (ph > 6.5)
    {
      mixersManager.mixBasic();
      data["mixed"] = "basic";
    }
    else if (ph < 5.5)
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
    Serial.println("[ATTUATORI] Terreno umido. Nessuna azione necessaria.");
    data["irrigation"] = false;
    data["mixed"] = "none";
  }

  // 5. Preparazione pacchetto Attuatori
  serializeJson(data, mixersBuffer);
  Serial.println("[TELEMETRIA ATTUATORI] Pronta per la dashboard:");
  serializeJsonPretty(data, Serial);
  Serial.println();
}

void loop()
{
}