// 7.c lookuptable
//
// g++ -Wall -o lookuptable lookuptable.cpp mijnsinus.cpp
// ./lookuptable

//TODO: zorg voor de juiste include
#include "lookuptable.hpp"

int main(int nArgc, char* aArgv[]) {

  // Initialiseren
  printf("7.c lookuptable\n\n");
  //TODO: zorg dat de sinus 20 x stappen en 10 y stappen groot is
  Mijnsinus oSinus(20, 10);

  // Toon de gegenereerde sinus
  for (uint16_t i = 0; i < oSinus.aantalX(); i++) {
    printf("%4d ", oSinus[i]);
  };

  // Afsluiten
  printf("\nAfgesloten :-)\n\n");

  return 0;
};