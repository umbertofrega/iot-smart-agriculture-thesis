#include <Arduino.h>
#include <EEPROM.h>
#include "DFRobot_ESP_PH_WITH_ADC.h"

class PhSensor
{
private:
    DFRobot_ESP_PH_WITH_ADC ph;
    int pin = A2;

public:
    PhSensor()
    {
    }

    void begin()
    {
        EEPROM.begin(32);
        ph.begin();
    }

    float getPh(int temperature)
    {
        float voltage = analogRead(pin) / 4095.0 * 3300.0;
        float phValue = ph.readPH(voltage, temperature);

        return (7.0 - (phValue - 7.0));
    }
};