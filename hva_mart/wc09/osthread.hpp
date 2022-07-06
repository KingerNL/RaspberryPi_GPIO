// GPIO:  5V 5V  G 14 15 18  G 23  24  G 25 08 07 IDSC  G 12  G 16 20 21
//       X-------------------------------------------------------------- 
// Pin :   2  4  6  8 10 12 14 16  18 20 22 24 26   28 30 32 34 36 38 40
// Pin :   1  3  5  7  9 11 13 15  17 19 21 23 25   27 29 31 33 35 37 39
//       --------------------------------------------------------------- 
// GPIO: 3V3 02 03 04  G 17 27 22 3V3 10 09 11  G IDSD 05 06 13 19 26  G

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
  #include "hardware.hpp"

  #define MAX_INVOER 100

  void printDC();
  void printLED();

  // De OS thread hardware laag class
  class OsThread {
    public:
      OsThread();
      ~OsThread();
      void join();
      void setup(int programs, std::vector <std::string> Namen);
      void run(int argc, char** Namen);
      void deactivate(int Window, int ActiveWin, std::string Naam);
      int activateFile(int Window, std::string Naam, FILE *bFile);
      int activateHard(int Window, std::string Naam);
      void CursUp(int MaxWin);
      void CursDown();
      std::vector <std::string> oScript;      

    private:
      int currprog;
      int height = 3;
      int width = 22;
      int starty = 3;
      int startx = 6;
      int curspos = -2;
      int currwin = 0;

      Knop KnopStopOS;
      Knop KnopUp;
      Knop KnopDown;
      Knop KnopStartProg;
      Knop KnopStopProg;
      
      void delay(long nMSec);
      static void *thread(void *pThreadData);

  };

#endif // _OSTHREAD_HPP_