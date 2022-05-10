// 5.c hwlayer
//
// g++ -pthread -o hwlayer hwlayer.cpp osthread.cpp knop.cpp led.cpp -I ~/hva_libraries/bcm2835/src ~/hva_libraries/bcm2835/src/bcm2835.c -fpermissive
// ./hwlayer

//TODO: voeg de juiste include toe
#include "hwlayer.hpp"

int main(int nArgc, char* aArgv[]) {

  // Initialiseren
  printf("5.c hwlayer\n\n");
  
  if (!bcm2835_init()) {
    printf("BCM init error!\n");
    return 1;
  };

  // Laad en start de OS hardware laag
  OsThread oOsThread;
  oOsThread.join();

  // Afsluiten na het wachten op de hoofdthread
  bcm2835_close();
  printf("\nAfgesloten :-)\n\n");

  return 0;
};