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
        EEPROM.begin(32);
<<<<<<< HEAD
        ph.begin();
=======
>>>>>>> fb719b0dae666259cb2b23a8b919f978895e9579
    }

    void calibrate(int temperature)
    {
        float voltage = analogRead(pin) / 4095.0 * 3300.0;

        return ph.calibration(temperature, voltage * 1.75);
    }

    float getPh(int temperature)
    {
        float voltage = analogRead(pin) / 4095.0 * 3300.0;
        float phValue = ph.readPH(voltage * 2, temperature);
        return phValue;
    }
};