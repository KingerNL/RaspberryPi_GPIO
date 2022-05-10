// 6.a mutex

//TODO: zorg voor de juiste include
#include "mutex.hpp"

void *ThreadLetters(void* pThreadData) {

  long nTid = (long)pThreadData;

  printf("ThreadLetters(%ld)\n", nTid);

  // Ga door tot het programma niet meer draait
  while (true) {

    for (char c = 'A'; c <= 'Z'; c++) {

      pthread_mutex_lock(&oLockOutput);
      printf("%c", c); fflush(stdout);
      pthread_mutex_unlock(&oLockOutput);
      thread_delay(100);

      // Stoppen?
      if (!_bRunning) {
        pthread_exit(NULL);
      };
    };
  };

  // Thread vrijgeven
  pthread_exit(NULL);
};