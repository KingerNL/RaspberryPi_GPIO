// 5.b hwdriver

#include "hwdriver.hpp"

void *Threads(void* pThreadData) {

  long nNr = (long)pThreadData;

  // Ga door tot drukknop 1
  while (true) {

    // Toon unieke thread tekst
    printf("T[%ld] ", nNr); fflush(stdout);
    thread_delay(250 + nNr * 100);

    // Stoppen?
    //TODO: zorg dat er gekeken wordt of de knop ingedrukt is
    if (oKnopStop.pushed() == 1 ) {
      _bRunning = false;
      pthread_exit(NULL);
    };
  };

  // Thread vrijgeven
  pthread_exit(NULL);
};
