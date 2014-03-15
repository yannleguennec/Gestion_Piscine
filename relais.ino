#include "relais.h"

#define nbRelays (sizeof(relaisPins) / sizeof(byte))
byte relaisPins[4] = { 2, 3, 4, 5 };
byte relaisVals[4] = { 0, 0, 0, 0 };

Relais::Relais(unsigned long interval) :
  Thread::Thread(interval)
{
  Serial.print("Relais::Relais(");
  Serial.print(interval);
  Serial.println(")");  
}

void Relais::setup(void)
{
  int i;
  
  Serial.print(millis());
  Serial.println(": Relais : Setup");
  
  for (i=0; i<nbRelays; i++)
  {
    pinMode(relaisPins[i], OUTPUT);
    digitalWrite(relaisPins[i], HIGH);
  }

}

void Relais::loop( unsigned long currentTime )
{
  int i;
  
  Serial.print(currentTime);
  Serial.println(": Relais::Loop()");
  
  for (i=0; i<nbRelays; i++)
  {
    int val = random(100) % 2;
    digitalWrite(relaisPins[i], relaisVals[i]);
  }
  
  i = random(0,4);
  int val = random(100) % 2;
  relaisVals[i] = 1-relaisVals[i];

}



