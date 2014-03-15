#ifndef affichage_h
#define affichage_h

#include "sequencer.h"

class Affichage : public Thread
{
  struct
  {
    unsigned char on;
    unsigned long previousTime;
  } backlight;
public: 
  Affichage(unsigned long interval);
  virtual void setup(void);
  virtual void loop( unsigned long currentTime );
};

#endif


