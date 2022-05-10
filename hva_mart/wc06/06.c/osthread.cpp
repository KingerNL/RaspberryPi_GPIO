
#include "osthread.hpp"
#include "progthread.hpp"

using namespace std;

FILE *pFile;
WINDOW *pWin1 = NULL; 
WINDOW *pWin2 = NULL; 
WINDOW* textwin = NULL; 
WINDOW *Prog1 = NULL;
WINDOW *Prog2 = NULL;
WINDOW *Prog3 = NULL;
WINDOW *Prog4 = NULL;
WINDOW *Prog5 = NULL;

OsThread::OsThread() {
  
  // Initialiseer de hardwarelaag voordat hij gebruikt gaat worden
  KnopUp.init(RPI_BPLUS_GPIO_J8_10);
  KnopDown.init(RPI_BPLUS_GPIO_J8_12);
  KnopStartProg.init(RPI_BPLUS_GPIO_J8_16); // rechterste button
  KnopStopProg.init(RPI_BPLUS_GPIO_J8_18);  // linkerste button
  KnopStopOS.init(RPI_BPLUS_GPIO_J8_22);   

  oLed1_.init(RPI_BPLUS_GPIO_J8_11);
  oLed2_.init(RPI_BPLUS_GPIO_J8_15);

};

OsThread::~OsThread() {

};

void OsThread::delay(long nMSec) {

  struct timespec oTime, oTimeLeft;

  // Handige delay-functie in msec
  oTime.tv_sec = 0; 
  oTime.tv_nsec = nMSec * 1000000L;
  nanosleep(&oTime, &oTimeLeft);
};

void OsThread::run(int argc, char** Namen){

  // Maak een string array en zet er alle programma's in.
  std::vector <string> v;
  //v.push_back("LEDS");
  for(int i = 1; i < argc; i++) {
  FILE * pFile = fopen(Namen[i], "r");
    if (pFile!=NULL) {
    v.push_back(Namen[i]);
    }
  }
  
  // Maak alle objects aan.
  ProgThread progs[v.size()];
  for (int i=0; i < v.size(); i++){
    progs[i].thread_id = i;
    progs[i].name = v[i];
  }

  initscr();
  refresh();

  int programs = v.size();
  setup(programs, v);

  // Ga door tot drukknop 1
  while (true) {

    // Wisselen?
    if (KnopUp.pushed()) {
      currwin ++;
      CursUp(programs);

      if (currwin > programs){ // verranderen naar: if currwin > nArgc.size().
        currwin = programs;    // verranderen naar: currwin = nArgc.size().
      }
    delay(300);
    }

    if (KnopDown.pushed()){

      currwin = currwin - 1;
      CursDown();

      if (currwin <= 0){ 
        currwin = 1; 
      }
    delay(300);
    }

    // Indrukken?
    if (KnopStartProg.pushed()){
      progs[currwin-1].start();
      currprog = activate(currwin, v);
      delay(300);
    }

    if (KnopStopProg.pushed()){
      progs[currwin-1].stop();
      deactivate(currwin, currprog, v);
      delay(300);
    }

    // Stoppen?
    if (KnopStopOS.pushed()) {
      endwin();
      break;
    };
  }
}

void OsThread::setup(int programs, std::vector <std::string> Namen){

 // Maak de twee windows en die er een box omheen.
 pWin1 = newwin(25, 32, 2, 4);
 
 box(pWin1, 0, 0);  
 wrefresh(pWin1);

 pWin2 = newwin(25, 60, 2, 43);
 box(pWin2, 0, 0);
 wmove(pWin2, 2, 1);
 whline(pWin2, '-', 58);
 wrefresh(pWin2);
 // Maak een sub window voor de tekst aan, en print hier prog1.txt op
 textwin = derwin(pWin2, 20, 58, 4, 1);
 
  // Maak de aantal programma's aan, afhankelijk van hoeveel arguments je hebt gehad. 
  for(int i = 1; i < programs+1; i++){

    string Mystring = Namen[i-1];

    if (i == 1){
        Prog1 = newwin(height, width, starty, startx);
        box(Prog1, 0, 0);
        mvwprintw(Prog1, 1, 2, "%s", Mystring.c_str());
        wrefresh(Prog1);
    }

    if (i == 2){
        Prog2 = newwin(height, width, starty, startx);
        box(Prog2, 0, 0);
        mvwprintw(Prog2, 1, 2, "%s", Mystring.c_str());
        wrefresh(Prog2);
    }

    if (i == 3){
        Prog3 = newwin(height, width, starty, startx);
        box(Prog3, 0, 0);
        mvwprintw(Prog3, 1, 2, "%s", Mystring.c_str());
        wrefresh(Prog3);
    }

    if (i == 4){
        Prog4 = newwin(height, width, starty, startx);
        box(Prog4, 0, 0);
        mvwprintw(Prog4, 1, 2, "%s", Mystring.c_str());
        wrefresh(Prog4);
    }

    if (i == 5){
        Prog5 = newwin(height, width, starty, startx);
        box(Prog5, 0, 0);
        mvwprintw(Prog5, 1, 2, "%s", Mystring.c_str());
        wrefresh(Prog5);
    }
    starty = starty + 4;
  }

}

int OsThread::activate(int Window, std::vector <std::string> Namen){
    
  string dastring = Namen[Window-1];

  const char* char_arr = dastring.c_str();
  pFile = fopen(char_arr, "r");  

  char sBuffer[59];

  // Verwijderd laatste text file en zet het op het scherm
  werase(textwin);
  while(feof(pFile) == 0){
   fgets(sBuffer, 56, pFile);
   wprintw(textwin, "%s", sBuffer);
  }
  wrefresh(textwin);

  WINDOW* a;
  switch (Window){
      case 1:
        a = Prog1;
        break;
      case 2:
        a = Prog2;
        break;
      case 3:
        a = Prog3;
        break;
      case 4:
        a = Prog4;
        break;
      case 5:
        a = Prog5;
        break;
  }
    mvwprintw(a, 1, 2, "%s <-", char_arr);
    wrefresh(a);
    mvwprintw(pWin2, 1, 2, "%s", char_arr);
    wrefresh(pWin2);
    return Window;
}

void OsThread::deactivate(int Window, int ActiveWin, std::vector <std::string> Namen){
  string dastring = Namen[Window-1];
  const char* char_arr = dastring.c_str();

  WINDOW* a;
  switch (Window){
      case 1:
        a = Prog1;
        break;
      case 2:
        a = Prog2;
        break;
      case 3:
        a = Prog3;
        break;
      case 4:
        a = Prog4;
        break;
      case 5:
        a = Prog5;
        break;
  }

  mvwprintw(a, 1, 2, "%s   ", char_arr);
  wrefresh(a);

  if (Window == ActiveWin){
      werase(textwin);
      wrefresh(textwin);
  }
}

void OsThread::CursUp(int MaxWin){

  mvwprintw(pWin1, curspos, 24, "   "); 

  curspos = curspos + 4;
  mvwprintw(pWin1, curspos, 24, "<--");

  

  if (curspos > MaxWin*4 ){ // Hier moet if curspos > Argc
    mvwprintw(pWin1, curspos, 24, "   ");
    curspos = (MaxWin*4) -2;
    mvwprintw(pWin1, curspos, 24, "<--");   
  }

  wrefresh(pWin1);

}

void OsThread::CursDown(){

  mvwprintw(pWin1, curspos, 24, "   "); 

  curspos = curspos - 4;
  mvwprintw(pWin1, curspos, 24, "<--");   

  if (curspos < 2){
    curspos = 2;
    mvwprintw(pWin1, curspos, 24, "<--");   
  }

  wrefresh(pWin1);

}

