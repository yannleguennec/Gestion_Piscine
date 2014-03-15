#ifndef pression_h
#define pression_h

#include "sequencer.h"

class Pression : public Thread
{
public: 
  Pression(unsigned long interval);
  virtual void setup(void);
  virtual void loop( unsigned long currentTime );
};

#endif
