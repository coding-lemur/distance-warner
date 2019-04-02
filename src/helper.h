#ifndef Helper_h
#define Helper_h

#include <Arduino.h>
#include <distance-sensor.h>

class Helper
{
public:
  static unsigned int getLedSpeed(DistanceSensor sensor);

private:
};
#endif