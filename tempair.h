#ifndef tempair_h
#define tempair_h

#include "sequencer.h"

class TempAir : public Thread
{
public: 
  TempAir(unsigned long interval);
  virtual void setup(void);
  virtual void loop( unsigned long currentTime );
};

#endif

