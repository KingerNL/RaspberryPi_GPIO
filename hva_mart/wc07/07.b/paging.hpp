// 7.b paging

#ifndef _PAGING_HPP_
#define _PAGING_HPP_

  #include <stdbool.h>
  #include <stdio.h>
  #include <string.h>
  #include <time.h>
  //TODO: zorg dat de Blokbuffer class bekend is
  #include "blokbuffer.hpp"
  // Maak #define voor handige delay-functie in msec
  #define thread_delay(nMSec) \
  { \
    struct timespec oTime, oTimeLeft; \
    oTime.tv_sec = 0; \
    oTime.tv_nsec = (nMSec) * 1000000L; \
    nanosleep(&oTime, &oTimeLeft); \
  };

//TODO: zorg voor het juiste #-commando
#endif