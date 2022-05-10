// 5.c hwlayer
//
// g++ -lncurses -pthread -o hwlayer hwlayer.cpp osthread.cpp knop.cpp led.cpp -I ~/hva_libraries/bcm2835/src ~/hva_libraries/bcm2835/src/bcm2835.c -fpermissive
// ./hwlayer

#include "hwlayer.hpp"
using namespace std;

int main(int nArgc, char* aArgv[]) {

  if (!bcm2835_init()) {
    printf("BCM init error!\n");
    return 1;
  };

  // Laad en start de OS hardware laag
  OsThread oOsThread;
  oOsThread.init(nArgc, aArgv);
  oOsThread.join();

  // Afsluiten na het wachten op de hoofdthread
  bcm2835_close();
  endwin();
  printf("\nAfgesloten :-)\n\n");

  return 0;
};