#include "tempeau.h"
#include <OneWire.h>

#define TEMPEAUPIN 10     // what pin we're connected to
OneWire tempEauSensor(TEMPEAUPIN);

TempEau::TempEau(unsigned long interval) :
  Thread::Thread(interval) 
{
  Serial.print("TempEau::TempEau(");
  Serial.print(interval);
  Serial.println(")");  
}

void TempEau::setup(void)
{
  Serial.print(millis());
  Serial.println(": TempEau : Setup");
}

void TempEau::loop( unsigned long currentTime )
{
  byte i;
  byte present = 0;
  byte addr[8]; // = {0x28, 0x4D, 0x84, 0x7C, 0x05, 0x00, 0x00, 0x7A};
  byte data[12];
  
  Serial.print(currentTime);
  Serial.println(": TempEau::loop()");

  /*
  if ( !tempEauSensor.search(addr)) {
    Serial.print("No more addresses.\n");
    tempEauSensor.reset_search();
    delay(250);
    return;
  }
  */
  tempEauSensor.reset_search();
  if ( !tempEauSensor.search(addr))
  {
    Serial.print("No more addresses.\n");
    return;
  }
  
  Serial.print("Addr=");
  for( i = 0; i < 8; i++) 
  {
    Serial.print(addr[i], HEX);
    Serial.print(" ");
  }
  
  if ( OneWire::crc8( addr, 7) != addr[7]) 
  {
      Serial.print("CRC is not valid!\n");
      return;
  }
  Serial.println();
  
  if ( addr[0] != 0x28)  // Should be 0x10 for DS12S20 according to datasheet !!! 
  {
      Serial.println("Device is not a DS18S20 family device.\n");
      return;
  }
  
  tempEauSensor.reset();
  tempEauSensor.select(addr);
  tempEauSensor.write(0x44);         // start conversion, with no parasite power on at the end
  
  while (!tempEauSensor.read()) ; // Wait for the sensor to complete
  
  present = tempEauSensor.reset();
  if (present)
  {
      tempEauSensor.select(addr);    
      tempEauSensor.write(0xBE);         // Read Scratchpad
      
      Serial.print("Reading data : ");
      for ( i = 0; i < 9; i++)           // we need 9 bytes
      {
        data[i] = tempEauSensor.read();
        Serial.print(data[i], HEX);
        Serial.print(" ");
      } 
      // Check CRC
      if ( OneWire::crc8( data, 8) != data[8]) {
        Serial.println("CRC is not valid!\n");
      }
      else
      {
        
        int value = (data[1] << 8) + data[0];
        int sign = value & 0x8000;  // test most sig bit
        if (sign) // negative
        {
          value = (value ^ 0xffff) + 1; // 2's comp
        }
        resultats.tempEau = (float)value * 0.0625;
        
        Serial.print(", TempEau: ");
        Serial.print(resultats.tempEau);
        Serial.println("*c");
      }
  }
  else Serial.println("Device not responding.");
}


