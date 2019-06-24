#include <distance-sensor.h>

DistanceSensor::DistanceSensor()
    : sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE),
      sensorAngleRad(SENSOR_ANGLE * (M_PI / 180)),         // calc deg to rad
      minDistance(MIN_SIDE_DISTANCE / cos(sensorAngleRad)) // cos(a) = ank / hyp)
{
}

void DistanceSensor::measure()
{
    distance = sonar.ping_cm();
    distanceSide = cos(sensorAngleRad) * distance;
    distanceRear = sin(sensorAngleRad) * distance;
}

unsigned int DistanceSensor::getDistance()
{
    return distance;
}

double DistanceSensor::getDistanceSide()
{
    return distanceSide;
}

double DistanceSensor::getDistanceRear()
{
    return distanceRear;
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