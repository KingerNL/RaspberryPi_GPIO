#include "windows.hpp"
#include "parser.hpp"
#include "runtime.hpp"
#include "hardware.hpp"
#include "player.hpp"

using namespace std;

std::mutex mtx;           // mutex for critical section

//Declareer de Variabelen
int yMax;
int xMax;
int x = 1;
int y = 1;
int stap = 2;
int cijfer;

WINDOW *pWin1 = NULL;
WINDOW *pWin2 = NULL;

void initWin(){

 // Start curses mode + refresh om te zien 
 initscr();
 refresh();

 //Krijg de maximale x,y coördinaten terug van het scherm, als je je scherm groter maakt. Zal dit verranderen
 getmaxyx(stdscr, yMax, xMax); 

 // Maak de twee windows en die er een box omheen.
 pWin1 = newwin(yMax/100*80, xMax/100*40, yMax/100*10, xMax/100*10);
 box(pWin1, 0, 0);
 wrefresh(pWin1);

 pWin2 = newwin(yMax/100*80, xMax/100*40, yMax/100*10, xMax/100*70);
 box(pWin2, 0, 0);
 wrefresh(pWin2);

};

// In dien er geklinkt wordt op je toetsenbord, verwijder beide windows en sluit het programma af.
void closeWin(){
  endwin();
}

// Hier wordt afgespeelt wat in Window 1 plaats neemt. Dit is optellen van 1 tot 1000. 
void prntWin1(){
 
 for (cijfer= 1; cijfer<= 279; cijfer++) {
  thread_delay(50);
  mvwprintw(pWin1, y, x, " %d", cijfer);
  wrefresh(pWin1);
  x = x+stap;
  
  if (cijfer== 9) {
   stap = stap+1;
  };
  
  if (cijfer== 99) {
   stap = stap+1;
  };
  
  if (x > 36) {
   y = y+1;
   x = 1;
  };

 };
};

// Hier wordt afgespeelt wat in Window 2 plaats neemt. Deze parsed eerst de ingekomen regels en speelt deze daarna ook af.
void prntWin2(){
 
 // Maak een Player aan en print deze in Window 2, op locatie 1,1 met het teken '@'
 Player * p = new Player(pWin2, 1, 1, '@');
 
 // Totdat de input geen x is, display de input en refresh het scherm.
 while(p->getmv()!='x') {
  mtx.lock();
  p-> display();
  wrefresh(pWin2);
  mtx.unlock();
 };
};