// 5.c hwlayer
//
// g++ -lncurses -pthread -o hwlayer hwlayer.cpp progthread.cpp osthread.cpp hardware.cpp -lbcm2835
// ./hwlayer Lorem.txt file2.txt Stickman.txt file4.txt ditisgeenfile.txt

#include "hwlayer.hpp"
using namespace std;

int main(int nArgc, char* aArgv[]) {

  if (!bcm2835_init()) {
    printf("BCM init error!\n");
    return 1;
  };

  // Laad en start de OS hardware laag
  OsThread OsThread;
  OsThread.run(nArgc, aArgv);

  // Afsluiten na het wachten op de hoofdthread
  bcm2835_close();
  endwin();

  return 0;
};