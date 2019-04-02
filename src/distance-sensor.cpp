#include <distance-sensor.h>

DistanceSensor::DistanceSensor(
    unsigned char triggerPin,
    unsigned char echoPin,
    unsigned int maxDistance,
    unsigned int minSideDistance,
    unsigned int angle)
    : sonar(triggerPin, echoPin, maxDistance),
      sensorAngleRad(angle * (M_PI / 180)),              // calc deg to rad
      minDistance(minSideDistance / cos(sensorAngleRad)) // cos(a) = ank / hyp)
{
}

void DistanceSensor::measure()
{
    distance = sonar.ping_cm();
    sideDistance = cos(sensorAngleRad) * distance;
    behindDistance = sin(sensorAngleRad) * distance;
}

unsigned int DistanceSensor::getDistance()
{
    return distance;
}

double DistanceSensor::getSideDistance()
{
    return sideDistance;
}

double DistanceSensor::getBehindDistance()
{
    return behindDistance;
}

double DistanceSensor::getMinDistance()
{
    return minDistance;
}

bool DistanceSensor::isTooClose()
{
    if (distance <= 0)
    {
        return false;
    }

    return distance <= minDistance;
}