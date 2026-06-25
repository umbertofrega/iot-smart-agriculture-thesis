#include <Arduino.h>
#include <EEPROM.h>
#include "DFRobot_ESP_PH_WITH_ADC.h"

class PhSensor
{
private:
    DFRobot_ESP_PH_WITH_ADC ph;
    int pin = GPIO_NUM_12;

public:
    PhSensor()
    {
        EEPROM.begin(32);
    }

    void calibrate(int temperature)
    {
        float voltage = analogRead(pin) / 4095.0 * 3300.0;
        return ph.calibration(temperature, voltage);
    }

    float getPh(int temperature)
    {
        float voltage = analogRead(pin) / 4095.0 * 3300.0;
        float phValue = ph.readPH(voltage, temperature);
        return phValue;
    }
};