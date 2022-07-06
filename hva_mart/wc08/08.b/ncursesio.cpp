// 8.b ncursesio
//
// g++ -Wall -lncurses -o ncursesio ncursesio.cpp hello-xmega-lib.cpp
// ./ncursesio

//TODO: zorg voor de juiste include
#include "ncursesio.hpp"

int main(int argc, char* argv[]) {

  char sUsbName[] = "/dev/ttyACM0";
  int nKey;
  bool bExit;
  uint8_t nByte;

  // Initialiseren
  initscr();
  clear();
  noecho();
  cbreak();
  raw();
  keypad(stdscr, true);
  nodelay(stdscr, true);

  printw("w4.2.2ncursesio\n\n"); refresh();

  // Initialiseer de correct Xmega-connectie (B38400 B57600 B115200)
  printw("> Verbinden: ");
  if (!InitXmegaSerial(sUsbName, B115200, 0)) {
    endwin();
    printf("Geen Xmega gevonden!\n");
    return -1;
  }
  else {
    printw(" OK\n");
  };
  refresh();

  // Blijf opvragen, versturen en tonen
  bExit = false;
  while (!bExit) {

    nKey = getch();

    // Exit is ESC
    if (nKey == 27) {
      bExit = true;
    };

    // Verwerk de toetsaanslag
    if (nKey != -1) {
      mvprintw(5,5, "Toets: %d=%c    ", nKey, nKey); refresh();
      XmegaWriteByte((uint8_t*)&nKey);
      while (!XmegaReadByte(&nByte));
      mvprintw(6,5, "Xmega: %d=%c    ", nByte, nByte); refresh();
    };
  };
  
  // Afsluiten
  endwin();
  printf("Afgesloten :-) ");
  if (!CloseXmegaSerial()) {
    printf(" fout\n");
  }
  else {
    printf(" OK\n");
  };

  return 0;
};