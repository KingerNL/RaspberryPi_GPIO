

#ifndef _OsThread_HPP_
#define _OsThread_HPP_

  #include <bcm2835.h>
  #include <stdbool.h>
  #include <stdio.h>
  #include <pthread.h>
  #include <vector>
  #include <ncurses.h>
  #include <thread>
  #include "hwlayer.hpp"
  #include "knop.hpp"
  #include "led.hpp"

  #define MAX_INVOER 100

  // De OS thread hardware laag class
  class OsThread {
    public:
      OsThread();
      ~OsThread();
      void join();
      void setup(int programs, std::vector <std::string> Namen);
      void run(int argc, char** Namen);
      void deactivate(int Window, int ActiveWin, std::vector <std::string> Namen);
      int activate(int Window, std::vector <std::string> Namen);
      void CursUp(int MaxWin);
      void CursDown();
      void LED();
      std::vector <std::string> oScript;      

    private:
      int currprog;
      int height = 3;
      int width = 22;
      int starty = 3;
      int startx = 6;
      int curspos = -2;
      int currwin = 0;
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