#include <Arduino.h>

#include <helper.h>
#include <animation.h>
#include <distance-sensor.h>

// ultra sonic sensor
#define TRIGGER_PIN 3
#define ECHO_PIN 2
#define MAX_DISTANCE 250      // cm
#define SENSOR_ANGLE 45       // deg
#define MIN_SIDE_DISTANCE 150 // cm
#define PING_SPEED 250        // ms

#define WARN_DURATION 2000  // ms
#define BLUETOOTH_SPEED 500 // ms

DistanceSensor sensor(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE, MIN_SIDE_DISTANCE, SENSOR_ANGLE);
Animation animation;

// timers
unsigned long now;
unsigned long sensorTimer = 0;
unsigned long warnTimer = 0;
unsigned long bluetoothTimer = 0;

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

      if (now >= bluetoothTimer)
      {
        // send data via Bluetooth
        Serial.print(sensor.getDistance());
        Serial.print(";");
        Serial.print(sensor.getSideDistance());
        Serial.print(";");
        Serial.println(sensor.getBehindDistance());

        bluetoothTimer = millis() + BLUETOOTH_SPEED;
      }
    }
  }

  if (now > warnTimer)
  {
    animation.stop();
  }

  animation.loop(ledSpeed);
}
