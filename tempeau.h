#ifndef tempeau_h
#define tempeau_h

#include "sequencer.h"

class TempEau : public Thread
{
public: 
  TempEau(unsigned long interval);
  virtual void setup(void);
  virtual void loop( unsigned long currentTime );
};

#endif

