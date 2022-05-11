
#include "osthread.hpp"
#include "progthread.hpp"

using namespace std;

FILE *pFile;
WINDOW *pWin1 = NULL; 
WINDOW *pWin2 = NULL; 
WINDOW *textwin = NULL; 
WINDOW *labelwin = NULL;
WINDOW *Prog1 = NULL;
WINDOW *Prog2 = NULL;
WINDOW *Prog3 = NULL;
WINDOW *Prog4 = NULL;
WINDOW *Prog5 = NULL;
char sBuffer[59];

OsThread::OsThread() {
  // Initialiseer de hardwarelaag voordat hij gebruikt gaat worden
  KnopUp.init(RPI_BPLUS_GPIO_J8_10);
  KnopDown.init(RPI_BPLUS_GPIO_J8_12);
  KnopStartProg.init(RPI_BPLUS_GPIO_J8_16); // rechterste button
  KnopStopProg.init(RPI_BPLUS_GPIO_J8_18);  // linkerste button
  KnopStopOS.init(RPI_BPLUS_GPIO_J8_22);   
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
    progs[i].File = fopen(progs[i].name.c_str(), "r");
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
      
      werase(labelwin);
      werase(textwin);
      // Laat huidige bestand zien, indien de curor erop staat. (Dus if currwin-1.staat == 1)
      if (progs[currwin-1].staat == 1){
        wprintw(labelwin, "%s", progs[currwin-1].name.c_str());
        
        // Verwijderd laatste text file en zet het op het scherm
        while(feof(progs[currwin-1].File) == 0){
          fgets(sBuffer, 56, progs[currwin-1].File);
          wprintw(textwin, "%s", sBuffer);
        }
      }

      wrefresh(textwin);
      wrefresh(labelwin); 
      fseek(progs[currwin-1].File, 0, SEEK_SET);
      delay(300);
    }

    if (KnopDown.pushed()){

      currwin = currwin - 1;
      CursDown();

      if (currwin <= 0){ 
        currwin = 1; 
      }
    
      werase(labelwin);
      werase(textwin);
      // Laat huidige bestand zien, indien de curor erop staat. (Dus if currwin-1.staat == 1)
      if (progs[currwin-1].staat == 1){
        wprintw(labelwin, "%s", progs[currwin-1].name.c_str());
        
        // Verwijderd laatste text file en zet het op het scherm
        while(feof(progs[currwin-1].File) == 0){
          fgets(sBuffer, 56, progs[currwin-1].File);
          wprintw(textwin, "%s", sBuffer);
        }
      }

      wrefresh(textwin);
      wrefresh(labelwin); 
      fseek(progs[currwin-1].File, 0, SEEK_SET);
      delay(300);
    }

    // Programma starten?
    if (KnopStartProg.pushed()){
      progs[currwin-1].start();
      currprog = activate(currwin, progs[currwin-1].name, progs[currwin-1].File);
      delay(300);
    }
 
    // Programma stoppen?
    if (KnopStopProg.pushed()){
      if (progs[currwin-1].staat == 1){
        progs[currwin-1].stop();
        deactivate(currwin, currprog, progs[currwin-1].name);
        delay(300);
      }

    }

    // OS Stoppen?
    if (KnopStopOS.pushed()){
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
 labelwin = derwin(pWin2, 1, 20, 1, 2);
 
  // Maak de aantal programma's aan, afhankelijk van hoeveel arguments je hebt gehad. 
  for(int i = 1; i < programs+1; i++){

    string Mystring = Namen[i-1];
    WINDOW *c = NULL;

    switch (i){
      case 1:
          c = Prog1 = newwin(height, width, starty, startx);
        break;
      case 2:
          c = Prog2 = newwin(height, width, starty, startx);
        break;
      case 3:
          c = Prog3 = newwin(height, width, starty, startx);
        break;
      case 4:
          c = Prog4 = newwin(height, width, starty, startx);
        break;
      case 5:
          c = Prog5 = newwin(height, width, starty, startx);
        break;
    }  
    
    mvwprintw(c, 1, 2, "%s", Mystring.c_str());
    box(c, 0, 0);
    wrefresh(c);
    starty = starty + 4;
  }

}

int OsThread::activate(int Window, std::string Naam, FILE *bFile){
 
  // Verwijderd laatste text file en zet het op het scherm
  werase(textwin);
  while(feof(bFile) == 0){
    fgets(sBuffer, 56, bFile);
    wprintw(textwin, "%s", sBuffer);
  }
  wrefresh(textwin);
  fseek(bFile, 0, SEEK_SET);
   
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
    mvwprintw(a, 1, 2, "%s <-", Naam.c_str());
    wrefresh(a);
    mvwprintw(pWin2, 1, 2, "%s", Naam.c_str());
    wrefresh(pWin2);
    return Window;
}

void OsThread::deactivate(int Window, int ActiveWin, std::string Naam){

  const char* char_arr = Naam.c_str();

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


  werase(textwin);
  werase(labelwin);
  wrefresh(textwin);
  wrefresh(labelwin);
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
