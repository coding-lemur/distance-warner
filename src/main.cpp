#include <Arduino.h>

#include <config.h>
#include <helper.h>
#include <animation.h>
#include <distance-sensor.h>

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
  pinMode(VOLTAGE_SENSOR_PIN, INPUT);

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
