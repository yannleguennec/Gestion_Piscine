#ifndef relais_h
#define relais_h

#include "sequencer.h"

class Relais : public Thread
{
public: 
  Relais(unsigned long interval);
  virtual void setup(void);
  virtual void loop( unsigned long currentTime );
  
};

#endif


