

class Sensor
{
public:
    virtual ~Sensor() {};

    virtual float readData() = 0;
};
