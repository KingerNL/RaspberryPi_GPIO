// 8.b ncursesio

#ifndef _NCURSESIO_HPP_
#define _NCURSESIO_HPP_

  //TODO: zorg dat ncurses beschikbaar is
  #include <ncurses.h>
  #include <stdbool.h>
  #include <stdio.h>
  #include <stdint.h>
  #include <string.h>
  #include <time.h>
  #include "hello-xmega-lib.hpp"

  // Maak #define voor handige delay-functie in msec
  #define thread_delay(nMSec) \
  { \
    struct timespec oTime, oTimeLeft; \
    oTime.tv_sec = 0; \
    oTime.tv_nsec = (nMSec) * 1000000L; \
    nanosleep(&oTime, &oTimeLeft); \
  };

#endif // _NCURSESIO_HPP_
