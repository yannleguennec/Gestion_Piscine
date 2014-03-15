#ifndef sequencer_h
#define sequencer_h

#include "commun.h"

#define Day * 24 Hr
#define Hr  * 60 Min
#define Min * 60 Sec
#define Sec * 1000 ms
#define ms  * 1

#define maxThreads 10

class Thread
{
public:
  Thread(unsigned long interval);
    
  unsigned long interval;
  unsigned long previousTime; 
  int pid;
  
  virtual void setup(void);
  virtual void loop(unsigned long currentTime);
 };

//**********************************************************************

class Sequencer
{
  public:
  
  static void reg(Thread *);
  static void setup(void);
  static void loop(void);
};


#endif

