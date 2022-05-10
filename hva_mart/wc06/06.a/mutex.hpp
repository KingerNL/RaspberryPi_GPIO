// 6.a mutex

#ifndef _MUTEX_HPP_
#define _MUTEX_HPP_

  #include <stdbool.h>
  #include <stdio.h>
  #include <time.h>
  #include <pthread.h>

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
  extern pthread_mutex_t oLockOutput;
  //TODO: zorg dat de thread ook in de main() gebruikt kan worden
  void *ThreadLetters(void* PthreadData);
  
#endif // _MUTEX_HPP_