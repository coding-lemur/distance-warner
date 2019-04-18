#include <helper.h>

unsigned int Helper::getLedSpeed(DistanceSensor sensor)
{
    // TODO use percent values to release dependency to fixed warn distance

    if (sensor.getDistance() <= 50)
    {
        return 3;
    }

    if (sensor.getDistance() <= 100)
    {
        return 2;
    }

    return 1;
}