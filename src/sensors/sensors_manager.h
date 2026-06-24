#include "temperature_sensor.h"
#include "ph_sensor.h"
#include "moisture_sensor.h"

class SensorsManager
{
private:
    float temperature;

public:
    SensorsManager()
    {
    }

    float getTemp()
    {
        return 0;
    }

    float getPh()
    {
        return 0;
    }

    float getHumidity()
    {
        return 0;
    }
};