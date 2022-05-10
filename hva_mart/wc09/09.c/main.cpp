// Code voor een miniatuur kolomboor, aangestuurd in c++.
// Alle includes van de Library's zijn te vinden in de windows.hpp
//
// Compiling wordt gedaan in de terminal met de volgende command:
// g++ -Wall -pthread -lncurses -o programma main.cpp windows.cpp parser.cpp runtime.cpp hardware.cpp player.cpp -lbcm2835
//
// Uitvoeren van het programma wordt gedaan met:
// sudo ./programma

#include "windows.hpp"
#include "parser.hpp"
#include "runtime.hpp"
#include "hardware.hpp"
using namespace std;

int main(){
 
 if (!bcm2835_init()){
  return 1;
 }
 
 // Initaliseer de twee windows & Hardware
 initWin();
 initHard();
  
 // Maak twee threads aan, beide voor hun eigen window
 std::thread Window1(prntWin1);
 std::thread Window2(prntWin2);

 initPars();

 // Laat main() wachten tot beide threads klaar zijn
 Window1.join();
 Window2.join();

 // Zet de dc aan, en laat hem draaien totdat de knop ingedrukt is
 DCaan();

 // Sluit het programma af
 closeWin();

};
