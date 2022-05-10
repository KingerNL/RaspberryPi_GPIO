// Voeg guards toe, om niet meerdere keren de hpp file toe te voegen aan de cpp files
#ifndef _WINDOWS_HPP_
#define _WINDOWS_HPP_

#include <ncurses.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <cstring>
#include <vector>
#include <string>
#include <bcm2835.h>
#include <thread>
#include <iostream>
#include <time.h>

// Maak een functie genaamd thread_delay
#define thread_delay(nMSec) \
{ \
  struct timespec oTime, oTimeLeft; \
  oTime.tv_sec = 0; \
  oTime.tv_nsec = (nMSec) * 1000000L; \
  nanosleep(&oTime, &oTimeLeft); \
};

// Declareer de functies
void initWin();
void closeWin();
void prntWin1();
void prntWin2();


#endif // _MULTITHREADING_HPP_