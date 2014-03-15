#include "commun.h"
#include "affichage.h"
#include "relais.h"
#include "tempair.h"
#include "tempeau.h"
#include "pression.h"

void setup()
{
  Serial.begin(115200);
  
  static Affichage affichageInstance(200 ms);
  static Relais relaisInstance(1275 ms);
  static TempAir tempAirInstance(5 Sec);
  static TempEau tempEauInstance(10 Sec);
  static Pression pressionInstance(7 Sec);
  
  Log(TITRE);
  Serial.print(":");
  Sequencer::setup();
}

int col=0;

void loop()
{

  Sequencer::loop();
  delay(1);
}

