
#include "osthread.hpp"
#include "progthread.hpp"

using namespace std;

FILE *pFile;
WINDOW *pWin1, *pWin2, *textwin, *labelwin, *Prog1, *Prog2, *Prog3, *Prog4, *Prog5, *Prog6, *WinLED1,  *WinLED2, *WinLED3, *WinDCaan, *WinDCuit;
char sBuffer[59];

OsThread::OsThread() {
  // Initialiseer de hardwarelaag voordat hij gebruikt gaat worden
  KnopStartProg.init(RPI_BPLUS_GPIO_J8_16); // linkerste button
  KnopUp.init(RPI_BPLUS_GPIO_J8_10); // tweede van links
  KnopStopProg.init(RPI_BPLUS_GPIO_J8_18);  // paars
  KnopDown.init(RPI_BPLUS_GPIO_J8_12); // Tweede van rechts
  KnopStopOS.init(RPI_BPLUS_GPIO_J8_08);   // (wit)

  KnopToggle.init(RPI_BPLUS_GPIO_J8_40);
  Knopswitch.init(RPI_BPLUS_GPIO_J8_38);
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
  
  // Initaliseer de LEDWindows en DCSTAAT
  int LEDWin;
  bool DCSTAAT = false;

  // Maak een string array en zet er alle programma's in.
  std::vector <string> v;
  for (int i = 1; i < argc; i++) {
    FILE * pFile = fopen(Namen[i], "r");
    if (pFile!=NULL) {
      v.push_back(Namen[i]);
    }
  }

  // Geef een error melding als er meer dan 4  bestaande .txt files gerunned willen worden
  if (v.size() > 4){
    std::cout << "ERROR: Te veel inputs! Er is een max van 4 files die er meegegeven kunnen worden. \n";
    return;
  }

  // Voeg de 2 programma's toe: DC-MOTOR & LEDS
  v.insert(v.begin(), "DC-MOTOR");
  v.insert(v.begin(), "LEDS");

  // Maak alle objects aan.
  ProgThread progs[v.size()];
  for (int i=0; i < v.size(); i++){
    progs[i].thread_id = i;
    progs[i].name = v[i];
    if (i > 1){
      progs[i].File = fopen(progs[i].name.c_str(), "r");
    }
  }

  // Initialiseer het screen en watch 10 miliseconden. Zodat het scherm 100% is geladen voordat je programma's inlaad
  initscr();
  refresh();
  delay(10);
  
  int programs = v.size();
  setup(programs, v);
  
  // Ga door tot drukknop "KnopStopOS"
  while (true) {
    
    // Wisselen van prog
    if (KnopUp.pushed()) {
      currwin ++;
      CursUp(programs);

      if (currwin > programs){
        currwin = programs;
      }
      
      werase(labelwin);
      werase(textwin);

      if (progs[currwin-1].staat == 1){ // Als het programma aan staat
        wprintw(labelwin, "%s", progs[currwin-1].name.c_str());
        if (currwin-1 > 1){ // Als het programma niet de eerste 2 programma's zijn.
          // Verwijderd laatste text file en zet het op het scherm
          while(feof(progs[currwin-1].File) == 0){
            fgets(sBuffer, 56, progs[currwin-1].File);
            wprintw(textwin, "%s", sBuffer);
          }
        }
        else {
          werase(textwin);
          if (progs[currwin-1].name == "LEDS"){
            // Maak een sub window voor de tekst aan, en print hier prog1.txt op
            printLED();
            LEDWin = 0;
          }
          else {
            printDC();
          }
          wrefresh(textwin);
        }
      }

      wrefresh(textwin);
      wrefresh(labelwin);
      if (currwin-1 > 1){
        fseek(progs[currwin-1].File, 0, SEEK_SET);
      }
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

      if (progs[currwin-1].staat == 1){ // Als het programma aan staat
        wprintw(labelwin, "%s", progs[currwin-1].name.c_str());
        if (currwin-1 > 1){ // Als het programma niet de eerste 2 programma's zijn.

          // Verwijderd laatste text file en zet het op het scherm
          while(feof(progs[currwin-1].File) == 0){
            fgets(sBuffer, 56, progs[currwin-1].File);
            wprintw(textwin, "%s", sBuffer);
          }
        }
        else {
          werase(textwin);
          if (progs[currwin-1].name == "LEDS"){
            // Maak een sub window voor de tekst aan, en print hier prog1.txt op
            printLED();
            LEDWin = 0;
          }
          else {
            printDC();
          }
          wrefresh(textwin);
        }
      }

      wrefresh(textwin);
      wrefresh(labelwin); 
      if (currwin-1 > 1){
        fseek(progs[currwin-1].File, 0, SEEK_SET);
      }
      delay(300);
    }

    // Programma starten
    if (KnopStartProg.pushed()){
      progs[currwin-1].start(progs[currwin-1].name);
      if (currwin-1 > 1){
        currprog = activateFile(currwin, progs[currwin-1].name, progs[currwin-1].File);
      }
      else {
          if (progs[currwin-1].name == "LEDS"){
            currprog = activateHard(currwin, progs[currwin-1].name);
          }
          else {
            currprog = activateHard(currwin, progs[currwin-1].name);
          }
      }
      delay(200);    
    }
 
    // Programma stoppen
    if (KnopStopProg.pushed()){
      progs[currwin-1].stop(progs[currwin-1].name);
      deactivate(currwin, currprog, progs[currwin-1].name);
      delay(200);
    }

    // DC MOTOR switch van window
    if (Knopswitch.pushed() && progs[currwin-1].name == "DC-MOTOR" ){
      if (progs[currwin-1].staat == 1){
        if (DCSTAAT == false){
          mvwprintw(WinDCuit, 2, 3, "DC-MOTOR UIT<-");
          mvwprintw(WinDCaan, 2, 3, "DC-MOTOR AAN  ");
          wrefresh(WinDCaan);
          wrefresh(WinDCuit);
        }
        else if (DCSTAAT == true){
          mvwprintw(WinDCuit, 2, 3, "DC-MOTOR UIT  ");
          mvwprintw(WinDCaan, 2, 3, "DC-MOTOR AAN<-");
          wrefresh(WinDCuit);
          wrefresh(WinDCaan);
        }
        delay(200);
        DCSTAAT = !DCSTAAT;
      }
    }

    // DC MOTOR klik op window
    if (KnopToggle.pushed() && progs[currwin-1].name == "DC-MOTOR" ){
      if (progs[currwin-1].staat == 1){
        if (DCSTAAT == false){
          progs[currwin-1].DCaan();
        }
        else if (DCSTAAT == true){
          progs[currwin-1].DCuit();
        }
      }
    }
    
    // LEDS switch van window
    if (Knopswitch.pushed() && progs[currwin-1].name == "LEDS" ){
      if (progs[currwin-1].staat == 1){
        LEDWin ++;
        if (LEDWin == 1){
          mvwprintw(WinLED3, 2, 5, "LED 3  ");
          mvwprintw(WinLED1, 2, 5, "LED 1<-");
          wrefresh(WinLED3);
          wrefresh(WinLED1);
        }
        if (LEDWin == 2){
          mvwprintw(WinLED1, 2, 5, "LED 1  ");
          mvwprintw(WinLED2, 2, 5, "LED 2<-");
          wrefresh(WinLED1);
          wrefresh(WinLED2);
        }
        if (LEDWin == 3){
          mvwprintw(WinLED2, 2, 5, "LED 2  ");
          mvwprintw(WinLED3, 2, 5, "LED 3<-");
          wrefresh(WinLED2);
          wrefresh(WinLED3);
          LEDWin = 0;
        }
        delay(200);
      }

    }

    // LEDS activeer / deactiveer
    if (KnopToggle.pushed() && progs[currwin-1].name == "LEDS" ){
      if (progs[currwin-1].staat == 1){      
        progs[currwin-1].LEDProg(LEDWin);
        delay(200);
      }
    }

    // OS Stoppen.
    if (KnopStopOS.pushed()){
      for (int i=0; i < v.size(); i++){
        if (progs[i].staat == 1) progs[i].stop(progs[i].name);
      }
      break;
    }
  }
}

// Set alle windows op, die nodig zijn voor de OS
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
    WINDOW *c ;

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
      case 6:
          c = Prog6 = newwin(height, width, starty, startx);
        break;
    }  
    
    mvwprintw(c, 1, 2, "%s", Mystring.c_str());
    box(c, 0, 0);
    wrefresh(c);
    starty = starty + 4;
  }

}

// Laat de File zien op het scherm
int OsThread::activateFile(int Window, std::string Naam, FILE *bFile){
 
  // Zet nieuwe text op het scherm
  werase(textwin);
  while(feof(bFile) == 0){
    fgets(sBuffer, 56, bFile);
    wprintw(textwin, "%s", sBuffer);
  }
  wrefresh(textwin);
  fseek(bFile, 0, SEEK_SET);
   
  WINDOW* a;
  switch (Window){
      case 3:
        a = Prog3;
        break;
      case 4:
        a = Prog4;
        break;
      case 5:
        a = Prog5;
        break;
        case 6:
        a = Prog6;
        break;
  }
    mvwprintw(a, 1, 2, "%s <-", Naam.c_str());
    wrefresh(a);
    mvwprintw(pWin2, 1, 2, "%s", Naam.c_str());
    wrefresh(pWin2);
    return Window;
}

// Laat de Hardware window zien op het scherm
int OsThread::activateHard(int Window, std::string Naam){

  werase(textwin);
  if (Naam == "LEDS"){
    // Maak een sub window voor de tekst aan, en print hier prog1.txt op
    printLED();
  }
  else {
    printDC();
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
  }
    mvwprintw(a, 1, 2, "%s <-", Naam.c_str());
    wrefresh(a);
    mvwprintw(pWin2, 1, 2, "%s", Naam.c_str());
    wrefresh(pWin2);
    return Window;
}

// Sluit het programma weer af.
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
      case 6:
        a = Prog6;
        break;
  }

  mvwprintw(a, 1, 2, "%s   ", char_arr);
  wrefresh(a);


  werase(textwin);
  werase(labelwin);
  wrefresh(textwin);
  wrefresh(labelwin);
}

// Laat de nav cursor 1 plek omhoog gaan, indien dit mogelijk is.
void OsThread::CursUp(int MaxWin){

  mvwprintw(pWin1, curspos, 24, "   "); 

  curspos = curspos + 4;
  mvwprintw(pWin1, curspos, 24, "<--");

  if (curspos > MaxWin*4 ){
    mvwprintw(pWin1, curspos, 24, "   ");
    curspos = (MaxWin*4) -2;
    mvwprintw(pWin1, curspos, 24, "<--");   
  }
  wrefresh(pWin1);
}

// Laat de nav cursor 1 plek omlaag gaan, indien dit mogelijk is.
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

// Print het DC programma naar het scherm (Hoort bij activateHard();).
void OsThread::printDC(){
    WinDCaan = derwin(textwin, 5, 20, 6, 4);
    WinDCuit = derwin(textwin, 5, 20, 6, 32);
    box(WinDCaan, 0, 0);
    box(WinDCuit, 0, 0);
    mvwprintw(WinDCaan, 2, 3, "DC-MOTOR AAN");
    mvwprintw(WinDCuit, 2, 3, "DC-MOTOR UIT");
    wrefresh(WinDCuit);
    wrefresh(WinDCaan);
}

// Print het LED programma naar het scherm (Hoort bij activateHard();).
void OsThread::printLED(){
    WinLED1 = derwin(textwin, 5, 16, 0, 20);
    WinLED2 = derwin(textwin, 5, 16, 7, 20);
    WinLED3 = derwin(textwin, 5, 16, 14, 20);

    box(WinLED1, 0, 0);
    box(WinLED2, 0, 0);
    box(WinLED3, 0, 0);

    mvwprintw(WinLED1, 2, 5, "LED 1");
    mvwprintw(WinLED2, 2, 5, "LED 2");
    mvwprintw(WinLED3, 2, 5, "LED 3");

    wrefresh(WinLED1);
    wrefresh(WinLED2);
    wrefresh(WinLED3);
}