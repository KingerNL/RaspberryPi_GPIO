// 5.b hwdriver
//
// g++ -pthread -o hwdriver hwdriver.cpp threads.cpp knop.cpp -lbcm2835
// ./hwdriver

//TODO: zorg voor de juiste include
#include "hwdriver.hpp"
#include "knop.hpp"
#include <iostream>
#include <vector>

//TODO: kies 3 oof meer threads
int NUM_THREADS = 5;

// Het programma begint
bool _bRunning = true;

// Globale hardware
Knop oKnopStop;

int main(int nArgc, char* aArgv[]) {
  
  std::vector <std::string> programs(aArgv + 1, aArgv + nArgc);
  
  for(int i = 0; i < programs.size(); i++){
    std::cout << ' ' << programs[0];
  }


   
  int nRet, i;
  pthread_t oThreads[NUM_THREADS];
  pthread_attr_t oAttr;
  void *pStatus;

  // Initialiseren
  printf("\n\n");
  if (!bcm2835_init()) {
    printf("BCM init error!\n");
    return 1;
  };

  oKnopStop.init(RPI_BPLUS_GPIO_J8_10);

  // Thread eigenschappen instellen
  pthread_attr_init(&oAttr);
  pthread_attr_setdetachstate(&oAttr, PTHREAD_CREATE_JOINABLE);

  for (i = 0; i < NUM_THREADS; i++) {
    nRet = pthread_create(&oThreads[i], &oAttr, Threads, (void*)(long)i); 
    if (nRet > 0) {
      printf("Thread kon niet gemaakt worden!\n");
      return -1;
    };
  };

  // Afsluiten door te wachten op de hoofdthread en daarna elke andere thread
  pthread_attr_destroy(&oAttr);
  printf("\nAfsluiten threads: "); fflush(stdout);
  for (i = 0; i < NUM_THREADS; i++) {
    pthread_join(oThreads[i], &pStatus); printf(" Thread[%i]=%ld ", i, (long)pStatus);
  };
  
  bcm2835_close();
  printf("\nAfgesloten :-)\n\n");

  return 0;
};