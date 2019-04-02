#ifndef DistanceSensor_h
#define DistanceSensor_h

#include <Arduino.h>
#include <NewPing.h>

class DistanceSensor
{

  public:
    DistanceSensor(
        unsigned char triggerPin,
        unsigned char echoPin,
        unsigned int maxDistance,
        unsigned int minSideDistance,
        unsigned int angle);

    void measure();
    unsigned int getDistance();
    double getSideDistance();
    double getBehindDistance();
    double getMinDistance();
    bool isTooClose();

  private:
    NewPing sonar;

    const float sensorAngleRad;
    const double minDistance;

    unsigned int distance;

    double sideDistance;
    double behindDistance;
};
#endif