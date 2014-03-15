#include "affichage.h"
#include "chars.h"
#include "LiquidCrystal_I2C.h"

LiquidCrystal_I2C lcd(0x27,16,2);
#define powerLedPin 13
#define buttonPin 12

#define BackLightInteval 15 Sec

Affichage::Affichage(unsigned long interval) :
  Thread::Thread(interval) 
{
  Serial.print("Affichage::Affichage(");
  Serial.print(interval);
  Serial.println(")");  
}

void Affichage::setup(void)
{
  pinMode(powerLedPin, OUTPUT);
  digitalWrite(powerLedPin, HIGH);
  
  pinMode(buttonPin, INPUT_PULLUP);
  
  Serial.print(millis());
  Serial.println(": Affichage : Setup");
  lcd.init();
  
  lcd.backlight();
  backlight.on=1;
  backlight.previousTime = millis();
  
  lcd.createChar(0, logos[0]);
  lcd.createChar(1, centigrade);
  lcd.createChar(2, farenheit);
  lcd.createChar(3, hPa);
  
  lcd.setCursor(0, 0);
  lcd.print(TITRE);
  lcd.setCursor(0, 1);
  lcd.print(VERSION);
  delay(1000);
  
  lcd.setCursor(0, 0);
  lcd.print("A:--.-  H:--.-%");
  lcd.setCursor(0, 1);
  lcd.print("E:--.-  P:---- ");
  lcd.setCursor(6,0);
  lcd.write(1);
  lcd.setCursor(6,1);
  lcd.write(1);
  lcd.setCursor(14,1);
  lcd.write(3);
  lcd.setCursor(15,0);
  lcd.write(0);
}

void Affichage::loop( unsigned long currentTime )
{
  int i;
  
  //digitalWrite(powerLedPin, 1-digitalRead(powerLedPin));
  
  Serial.print(currentTime);
  Serial.println(": Affichage : Loop");
  lcd.setCursor(2, 0);
  if (resultats.tempAir<10) lcd.print("0");
  lcd.print(resultats.tempAir,1);
  lcd.setCursor(10, 0);
  if (resultats.humidite<10) lcd.print("0");
  lcd.print(resultats.humidite,1);
  lcd.setCursor(2, 1);
  if (resultats.tempEau<10) lcd.print("0");
  lcd.print(resultats.tempEau,1);
  lcd.setCursor(10, 1);
  if (resultats.pression<100000) lcd.print(" ");
  if (resultats.pression<10000) lcd.print(" ");
  if (resultats.pression<1000) lcd.print(" ");
  lcd.print(resultats.pression/100,0);
  
  static int logo=0;
  lcd.createChar(0, logos[logo]);
  logo=(logo+1)%nbLogos;
  
  //Serial.print("Backlight: ");
  //Serial.print(backlight.on);
  //Serial.print(", button: ");
  //Serial.print(digitalRead(buttonPin));
  //Serial.print(", previousTime: ");
  //Serial.print(backlight.previousTime);
  //Serial.println();
  
  if (digitalRead(buttonPin) == 0)
    backlight.previousTime = currentTime;
    
  if (backlight.on)
  {
    if (currentTime - backlight.previousTime > BackLightInteval)
    {
      Serial.println("Backlight off");
      lcd.noBacklight();    
      backlight.on=0;
    }
  }
  else
  {
    if (digitalRead(buttonPin) == 0)
    {
      Serial.println("Backlight on");
      lcd.backlight();
      backlight.on=1;
      backlight.previousTime = currentTime;
    }
  }
}



