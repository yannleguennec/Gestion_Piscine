#include "pression.h"
#include <Wire.h>
#include <Adafruit_BMP085.h>

Adafruit_BMP085 pressionSensor;
byte pressionSensorFound = 0;

#define pressionMer 101325 /* Pa */

Pression::Pression(unsigned long interval) :
  Thread::Thread(interval) 
{
  Serial.print("Pression::Pression(");
  Serial.print(interval);
  Serial.println(")");  
  if (!pressionSensor.begin()) {
    Serial.println("Could not find a valid BMP085 sensor, check wiring!");
    pressionSensorFound = 1;
  }
  Serial.print("Ok");
}

void Pression::setup(void)
{
  Serial.println("Pression::setup()");
}

void Pression::loop( unsigned long currentTime )
{
  Serial.print(currentTime);
  Serial.println(": Pression::Loop()");

  resultats.tempAir2 = pressionSensor.readTemperature();
  resultats.pression = pressionSensor.readPressure();
  resultats.altitude = pressionSensor.readAltitude(pressionMer);
  Serial.print("Temperature: ");
  Serial.print(resultats.tempAir2);
  Serial.print("*c, Pression: ");
  Serial.print(resultats.pression);
  Serial.print("Pa, Altitude: ");
  Serial.print(resultats.altitude);
  Serial.println("m");
}


