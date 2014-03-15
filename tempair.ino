#include "TempAir.h"
#include "DHT.h"

#define TEMPAIRPIN 7     // what pin we're connected to
#define TEMPAIRTYPE DHT11   // DHT 11 
DHT tempAirSensor(TEMPAIRPIN,TEMPAIRTYPE);

TempAir::TempAir(unsigned long interval) :
  Thread::Thread(interval) 
{
  Serial.print("TempAir::TempAir(");
  Serial.print(interval);
  Serial.println(")");  
}

void TempAir::setup(void)
{
  Serial.print(millis());
  Serial.println(": TempAir : Setup");
  tempAirSensor.begin();
}

void TempAir::loop( unsigned long currentTime )
{
  Serial.print(currentTime);
  Serial.println(": TempAir::loop()");
  resultats.humidite = tempAirSensor.readHumidity();
  resultats.tempAir  = tempAirSensor.readTemperature();
  if (isnan(resultats.tempAir) || isnan(resultats.humidite)) {
    Serial.println("Failed to read from DHT");
  } else {
    Serial.print("Temperature : ");
    Serial.print(resultats.tempAir);
    Serial.print(" *C, Humidite : ");
    Serial.print(resultats.humidite);
    Serial.println("%");
  }
  
 
}


