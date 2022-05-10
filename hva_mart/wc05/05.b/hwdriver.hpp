// 5.b hwdriver

#ifndef _HWDRIVER_HPP_
#define _HWDRIVER_HPP_

  #include <bcm2835.h>
  #include <stdbool.h>
  #include <stdio.h>
  #include <string.h>
  #include <time.h>
  //TODO: zorg voor includes pthread en ...?
  #include <pthread.h>
  #include "knop.hpp"

  // Maak #define voor handige delay-functie in msec
  #define thread_delay(nMSec) \
  { \
    struct timespec oTime, oTimeLeft; \
    oTime.tv_sec = 0; \
    oTime.tv_nsec = (nMSec) * 1000000L; \
    nanosleep(&oTime, &oTimeLeft); \
  };

  // Mijn threads
  extern bool _bRunning;
  void *Threads(void* pThreadData);

  // Globale hardware
  extern Knop oKnopStop;

#endif // _HWDRIVER_HPP_