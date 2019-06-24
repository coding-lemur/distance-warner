#ifndef DistanceSensor_h
#define DistanceSensor_h

#include <NewPing.h>
#include <config.h>

class DistanceSensor
{

public:
  DistanceSensor();

  void measure();
  unsigned int getDistance();
  double getDistanceSide();
  double getDistanceRear();
  double getMinDistance();
  bool isTooClose();

private:
  NewPing sonar;

  const float sensorAngleRad;
  const double minDistance;

  unsigned int distance;

  double distanceSide;
  double distanceRear;
};
#endif