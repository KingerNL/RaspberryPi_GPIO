// 6.a mutex
//
// g++ -Wall -pthread -o mutex mutex.cpp threadletters.cpp
// ./mutex

//TODO: voeg de juiste include toe
#include "mutex.hpp"

// Het programma begint
bool _bRunning = true;

//TODO: zorg dat de mutex variable een instantie krijgt om te kunnen gebruiken
pthread_mutex_t oLockOutput;

int main(int nArgc, char* aArgv[]) {

  int nRet, i;
  pthread_t oThreadLetters;
  pthread_attr_t oAttr;
  void *pStatus;

  // Initialiseren
  printf("6.a mutex\n\n");

  // Mutex aanmaken voordat de thread gemaakt en gestart wordt
  nRet = pthread_mutex_init(&oLockOutput, NULL);
  if (nRet > 0) {
    printf("Mutex kon niet gemaakt worden!\n");
    return -1;
  };

  // Thread eigenschappen instellen
  pthread_attr_init(&oAttr);
  pthread_attr_setdetachstate(&oAttr, PTHREAD_CREATE_JOINABLE);

  nRet = pthread_create(&oThreadLetters, &oAttr, ThreadLetters, (void*)123); 
  if (nRet > 0) {
    printf("Thread kon niet gemaakt worden!\n");
    return -1;
  };

  // Een tijdelijk loop om het effect van de mutex te laten zien
  for (i = 0; i < 25; i++) {
    
    pthread_mutex_lock(&oLockOutput);
    printf(" main "); fflush(stdout);
    //TODO: voeg een delay van 750 msec toe
    thread_delay(750);
    pthread_mutex_unlock(&oLockOutput);

    thread_delay(750);
  };
  _bRunning = false;

  // Afsluiten door te wachten op de hoofdthread en daarna elke andere thread
  pthread_attr_destroy(&oAttr);
  printf("\nAfsluiten threads: "); fflush(stdout);
  pthread_join(oThreadLetters, &pStatus); printf(" ThreadLetters=%ld ", (long)pStatus);
  
  pthread_mutex_destroy(&oLockOutput);

  printf("\nAfgesloten :-)\n\n");
  return 0;
};
