#include <Arduino.h>

#include <config.h>
#include <helper.h>
#include <animation.h>
#include <distance-sensor.h>

DistanceSensor sensor;
Animation animation;

// timers
unsigned long now;
unsigned long sensorTimer = 0;
unsigned long warnTimer = 0;
unsigned long dataTimer = 0;

byte ledSpeed = 1;

void setup()
{
  Serial.begin(9600);

  Serial.println("distance-warner connected!");

  Serial.print("min distance: ");
  Serial.println(sensor.getMinDistance());

  animation.setup();
}

void loop()
{
  now = millis();

  if (now >= sensorTimer)
  {
    sensorTimer = now + PING_SPEED;

    sensor.measure();

    if (sensor.isTooClose())
    {
      warnTimer = millis() + WARN_DURATION;
      ledSpeed = Helper::getLedSpeed(sensor);

      animation.start();

      if (now >= dataTimer)
      {
        dataTimer = millis() + BLUETOOTH_SPEED;

        // send data via serial port
        Serial.print(sensor.getDistance());
        Serial.print(";");
        Serial.print(sensor.getDistanceSide());
        Serial.print(";");
        Serial.println(sensor.getDistanceRear());
      }
    }
  }

  if (now > warnTimer)
  {
    animation.stop();
  }

  animation.loop(ledSpeed);
}
