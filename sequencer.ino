#include "sequencer.h";

Thread::Thread(unsigned long interval)
{
  this->interval = interval;
  this->previousTime = 0;
  Sequencer::reg(this);
  Serial.print("Thread ");
  Serial.print(this->pid);
  Serial.println("::Thread()");
  
  
}

void Thread::setup(void)
{
  Serial.print("Thread ");
  Serial.print(this->pid);
  Serial.println("::setup()");
};

void Thread::loop(unsigned long currentTime) 
{
  Serial.print("Thread ");
  Serial.print(this->pid);
  Serial.print("::loop(");
  Serial.print(currentTime);
  Serial.println(")");
};

//************************************************************************

Thread *threads[maxThreads];
int nbThread = 0;

void Sequencer::reg(Thread *thread)
{
  threads[ nbThread++ ] = thread;
  thread->pid = nbThread;
  
  Serial.print("Adding Thread ");
  Serial.println( nbThread );
}

void Sequencer::setup(void)
{
  unsigned short currentTime = millis();
  int i;

  Serial.println("Sequencer::setup()");
  
  for (i=0; i<nbThread; i++)
    threads[i]->setup();
}

void Sequencer::loop(void)
{
  unsigned long currentTime = millis();
  int i;

  //Serial.println("Sequencer::loop()");
  
  for (i=0; i<nbThread; i++) 
  {
    Thread *thread = threads[i];
    if (currentTime - thread->previousTime > thread->interval)
    {
      thread->loop(currentTime);
      while (currentTime - thread->previousTime > thread->interval)
        thread->previousTime += thread->interval;
    }
  }
}




