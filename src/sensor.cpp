#include <Adafruit_BME280.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

#include "sensor.h"

Adafruit_BME280 bme;

float temp, hum, pres;

bool initSensor()
{
  return bme.begin(0x76);
}

void readSensor()
{
  temp = bme.readTemperature();
  hum = bme.readHumidity();
  pres = bme.readPressure() / 100.0;
}

float getTemperature()
{
  return temp;
}

float getHumidity()
{
  return hum;
}

float getPressure()
{
  return pres;
}

int getBatteryLevel()
{
  // Placeholder for battery level reading logic
  // In a real implementation, this would read from an ADC pin or similar
  return 100; // Assume full battery for now
}