// 7.c lookuptable

#ifndef _LOOKUPTABLE_HPP_
#define _LOOKUPTABLE_HPP_

  #include <stdbool.h>
  #include <stdio.h>
  #include <string.h>
  //TODO: zorg voor de include die nanosleep() bevat
  #include <time.h>
  #include "mijnsinus.hpp"

  // Maak #define voor handige delay-functie in msec
  #define thread_delay(nMSec) \
  { \
    struct timespec oTime, oTimeLeft; \
    oTime.tv_sec = 0; \
    oTime.tv_nsec = (nMSec) * 1000000L; \
    nanosleep(&oTime, &oTimeLeft); \
  };

#endif // _LOOKUPTABLE_HPP_