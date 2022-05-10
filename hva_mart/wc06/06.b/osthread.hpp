// 5.c hwlayer

//TODO: zorg voor de juiste # commando's
#ifndef _OSTHREAD_HPP_
#define _OSTHREAD_HPP_

  #include <bcm2835.h>
  #include <stdbool.h>
  #include <stdio.h>
  #include <pthread.h>
  #include <ncurses.h>
  //TODO: zorg dat de Knop en Led class bekend zijn
  #include "hwlayer.hpp"
  #include "knop.hpp"
  #include "led.hpp"
  
  #define MAX_INVOER 100
  
  void deactivate(int Window);
  void activate(int Window);
  void CursUp();
  void CursDown();

  // De OS thread hardware laag class
  class OsThread {
    public:
      OsThread();
      ~OsThread();
      void join();
      void init(int programs, char** Namen);
      std::vector <std::string> oScript;

    private:
      pthread_t oThread_;
      pthread_attr_t oAttr_;

      Knop KnopStopOS;
      Knop KnopUp;
      Knop KnopDown;
      Knop KnopStartProg;
      Knop KnopStopProg;

      Led oLed1_;
      Led oLed2_;

      void delay(long nMSec);
      static void *thread(void *pThreadData);

  };

#endif // _OSTHREAD_HPP_