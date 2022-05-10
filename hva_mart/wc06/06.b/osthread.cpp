// GPIO:  5V 5V  G 14 15 18  G 23  24  G 25 08 07 IDSC  G 12  G 16 20 21
//       X-------------------------------------------------------------- 
// Pin :   2  4  6  8 10 12 14 16  18 20 22 24 26   28 30 32 34 36 38 40
// Pin :   1  3  5  7  9 11 13 15  17 19 21 23 25   27 29 31 33 35 37 39
//       --------------------------------------------------------------- 
// GPIO: 3V3 02 03 04  G 17 27 22 3V3 10 09 11  G IDSD 05 06 13 19 26  G

// 5.c hwlayer
using namespace std;
#include "osthread.hpp"

FILE *pFile;
WINDOW *pWin1 = NULL; // Selectie menu
WINDOW *pWin2 = NULL; // Programma display
WINDOW* textwin = NULL; // 

WINDOW *Prog1 = NULL;
WINDOW *Prog2 = NULL;
WINDOW *Prog3 = NULL;
WINDOW *Prog4 = NULL;
WINDOW *Prog5 = NULL;

int height = 3;
int width = 22;
int starty = 3;
int startx = 6;
int curspos = -2;
int currwin = 0;

OsThread::OsThread() {
  
  // Initialiseer de hardwarelaag voordat hij gebruikt gaat worden
  KnopUp.init(RPI_BPLUS_GPIO_J8_10);
  KnopDown.init(RPI_BPLUS_GPIO_J8_12);
  KnopStartProg.init(RPI_BPLUS_GPIO_J8_16); // rechterste button
  KnopStopProg.init(RPI_BPLUS_GPIO_J8_18);  // linkerste button
  KnopStopOS.init(RPI_BPLUS_GPIO_J8_22);   

  oLed1_.init(RPI_BPLUS_GPIO_J8_11);
  oLed2_.init(RPI_BPLUS_GPIO_J8_15);

  // Initialiseer de thread instellingen
  pthread_attr_init(&oAttr_);
  pthread_attr_setdetachstate(&oAttr_, PTHREAD_CREATE_JOINABLE);

  // Maak de thread zelf en koppel de class instantie via het dataveld
  int nRet = pthread_create(&oThread_, &oAttr_, thread, (void*)this); 
  if (nRet > 0) {
    printf("OsThread kon niet gemaakt worden!\n");
    return;
  };
};

OsThread::~OsThread() {

  // Vrijgeven thread instellingen
  pthread_attr_destroy(&oAttr_);
};

void OsThread::join() {

  void *pStatus;

  // Wacht tot de thread klaar is
  pthread_join(oThread_, &pStatus); 
};

void OsThread::delay(long nMSec) {

  struct timespec oTime, oTimeLeft;

  // Handige delay-functie in msec
  oTime.tv_sec = 0; 
  oTime.tv_nsec = nMSec * 1000000L;
  nanosleep(&oTime, &oTimeLeft);
};

void *OsThread::thread(void *pThreadData) {

  OsThread *pThis;
  pThis = (OsThread*)pThreadData;

  // Ga door tot drukknop 1
  while (true) {
    // Toon unieke thread tekst
    fflush(stdout);
    pThis->delay(200);

    // Wisselen?
    if (pThis->KnopUp.pushed()) {

      currwin ++;
      CursUp();

      if (currwin == 4){ // verranderen naar: if currwin > nArgc.length().
        currwin = 3;    // verranderen naar: currwin = nArgc.length().
      }
    }

    if (pThis->KnopDown.pushed()){

      currwin = currwin - 1;
      CursDown();

      if (currwin < 0){ 
        currwin = 1; 
      }
    }

    // Indrukken?
    if (pThis->KnopStartProg.pushed()){
      activate(currwin);
    }  

    if (pThis->KnopStopProg.pushed()){
      deactivate(currwin);
    }

    // Stoppen?
    if (pThis->KnopStopOS.pushed()) {
      pthread_exit(NULL);
    };
  };
 
  // Thread vrijgeven
  pthread_exit(NULL);
};

void activate(int Window){
    
  //pFile = fopen(Namen[1], "r");  

  char sBuffer[59];

  while(feof(pFile) == 0){
   fgets(sBuffer, 56, pFile);
   wprintw(textwin, "%s", sBuffer);
  }

  if (Window== 1){
    mvwprintw(Prog1, 1, 2, "prog1.txt <-"); // Verrander "Programma 1", naar %s, argv[1] + <-
    mvwprintw(pWin2, 1, 2, "prog1.txt");
    wrefresh(Prog1);
    wrefresh(pWin2);
  }
  else if (Window== 2){
    mvwprintw(Prog2, 1, 2, "prog2.txt <-"); // Verrander "Programma 2", naar argv[2] + <-
    mvwprintw(pWin2, 1, 2, "prog2.txt");
    wrefresh(Prog2);
    wrefresh(pWin2);
  }
  else if (Window== 3){
    mvwprintw(Prog3, 1, 2, "prog3.txt <-"); // Verrander "Programma 3", naar argv[3] + <-
    mvwprintw(pWin2, 1, 2, "prog3.txt");
    wrefresh(Prog3);
    wrefresh(pWin2);
  }
  else if (Window== 4){
    mvwprintw(Prog4, 1, 2, "prog4.txt <-"); // Verrander "Programma 4", naar argv[4] + <-
    mvwprintw(pWin2, 1, 2, "prog4.txt");
    wrefresh(Prog4); 
    wrefresh(pWin2);
  }
  else if (Window== 5){
    mvwprintw(Prog5, 1, 2, "prog5.txt <-"); // Verrander "Programma 5", naar argv[5] + <-
    mvwprintw(pWin2, 1, 2, "prog5.txt");
    wrefresh(Prog5);
    wrefresh(pWin2);
  }
    
}

void deactivate(int Window){
  init_pair(1, COLOR_WHITE, COLOR_BLACK);
  
  if (Window== 1){
    mvwprintw(Prog1, 1, 2, "prog1.txt   "); // Verrander "Programma 1", naar argv[1]
    wrefresh(Prog1);
  }
  else if (Window== 2){
        mvwprintw(Prog2, 1, 2, "prog2.txt   "); // Verrander "Programma 2", naar argv[2]
        wrefresh(Prog2);
    }
  else if (Window== 3){
        mvwprintw(Prog3, 1, 2, "prog3.txt   "); // Verrander "Programma 3", naar argv[3]
        wrefresh(Prog3);
    }
  else if (Window== 4){
        mvwprintw(Prog4, 1, 2, "prog4.txt   "); // Verrander "Programma 4", naar argv[4]
        wrefresh(Prog4); 
    }
  else if (Window== 5){
        mvwprintw(Prog5, 1, 2, "prog5.txt   "); // Verrander "Programma 5", naar argv[5]
        wrefresh(Prog5);
    }
}

void CursUp(){

  mvwprintw(pWin1, curspos, 24, "   "); 

  curspos = curspos + 4;
  mvwprintw(pWin1, curspos, 24, "<--");

  if (curspos > 10 ){ // Hier moet if curspos > nArgc
    mvwprintw(pWin1, curspos, 24, "   ");
    curspos = 10;
    mvwprintw(pWin1, curspos, 24, "<--");   
  }

  wrefresh(pWin1);

}

void CursDown(){

  mvwprintw(pWin1, curspos, 24, "   "); 

  curspos = curspos - 4;
  mvwprintw(pWin1, curspos, 24, "<--");   

  if (curspos < 2){
    curspos = 2;
    mvwprintw(pWin1, curspos, 24, "<--");   
  }

  wrefresh(pWin1);

}

void OsThread::init(int programs, char** Namen) {
 
 initscr();
 refresh();

 char sBuffer[59];

 oScript.resize(programs);
 for (int i = 1; i < programs; i++) {
  oScript.push_back(Namen[i]);  // Voegt naam in argv[i] toe aan het eind van de vector. 
 };

 // Maak de twee windows en die er een box omheen.
 pWin1 = newwin(25, 32, 2, 4);
 
 box(pWin1, 0, 0);  
 wrefresh(pWin1);

 pFile = fopen(Namen[1], "r");
 //fgets(sBuffer, 58, pFile);

 pWin2 = newwin(25, 60, 2, 43);
 box(pWin2, 0, 0);
 mvwprintw(pWin2, 1, 2, "%s", Namen[1]);
 wmove(pWin2, 2, 1);
 whline(pWin2, '-', 58);
 wrefresh(pWin2);

 // Maak een sub window voor de tekst aan, en print hier prog1.txt op
 textwin = derwin(pWin2, 20, 58, 4, 1);

 while(feof(pFile) == 0){
  fgets(sBuffer, 56, pFile);
  wprintw(textwin, "%s", sBuffer);
 }

 wrefresh(textwin);
 refresh();

  // Maak de aantal programma's aan, afhankelijk van hoeveel arguments je hebt gehad. 
  for(int i = 1; i < programs; i++){

    start_color();
    if (i == 1){
        Prog1 = newwin(height, width, starty, startx);
        box(Prog1, 0, 0);
        mvwprintw(Prog1, 1, 2, "%s", Namen[i]);
        wrefresh(Prog1);
    }

    if (i == 2){
        Prog2 = newwin(height, width, starty, startx);
        box(Prog2, 0, 0);
        mvwprintw(Prog2, 1, 2, "%s", Namen[i]);
        wrefresh(Prog2);
    }

    if (i == 3){
        Prog3 = newwin(height, width, starty, startx);
        box(Prog3, 0, 0);
        mvwprintw(Prog3, 1, 2, "%s", Namen[i]);
        wrefresh(Prog3);
    }

    if (i == 4){
        Prog4 = newwin(height, width, starty, startx);
        box(Prog4, 0, 0);
        mvwprintw(Prog4, 1, 2, "%s", Namen[i]);
        wrefresh(Prog4);
    }

    if (i == 5){
        Prog5 = newwin(height, width, starty, startx);
        box(Prog5, 0, 0);
        mvwprintw(Prog5, 1, 2, "%s", Namen[i]);
        wrefresh(Prog5);
    }
    starty = starty + 4;
  }
}
