// 7.a cyclischbuffer
//
// g++ -Wall -o cyclischbuffer cyclischbuffer.cpp buffer.cpp
// ./cyclischbuffer

#include "cyclischbuffer.hpp"


int main(int nArgc, char* aArgv[]) {

  // Initialiseren
  printf("7.a cyclischbuffer\n\n");
  
  Buffer oBuf(40);
  printf("> lengte=%d blok=%d gevuld=%d isleeg=%c\n", oBuf.lengte(), oBuf.blok(), oBuf.gevuld(), oBuf.isLeeg() ? 'j' : 'n');

  // Vul een stuk
  printf("> push A..Z\n");
  for (unsigned char c = 'A'; c < 'Z'; c++) {
    oBuf.push(c);
    //TODO: zorg dat c een push in oBuf krijgt
  };
  printf("> lengte=%d blok=%d gevuld=%d isleeg=%c\n", oBuf.lengte(), oBuf.blok(), oBuf.gevuld(), oBuf.isLeeg() ? 'j' : 'n');

  // Krijg een deel
  printf("> pull: ");
  for (unsigned char c = 0; c < 10; c++) {
    printf("%c ", oBuf.pull());
  };
  printf("\n");
  printf("> lengte=%d blok=%d gevuld=%d isleeg=%c\n", oBuf.lengte(), oBuf.blok(), oBuf.gevuld(), oBuf.isLeeg() ? 'j' : 'n');

  // Overvul een stuk
  printf("> push A..Z A..Z\n");
  for (unsigned char c = 'A'; c < 'Z'; c++) {
    oBuf.push(c);
  };
  for (unsigned char c = 'A'; c < 'Z'; c++) {
    oBuf.push(c);
  };
  printf("> lengte=%d blok=%d gevuld=%d isleeg=%c\n", oBuf.lengte(), oBuf.blok(), oBuf.gevuld(), oBuf.isLeeg() ? 'j' : 'n');

  // Krijg een deel
  printf("> pull: ");
  for (unsigned char c = 0; c < 10; c++) {
    printf("%c ", oBuf.pull());
  };
  printf("\n");
  printf("> lengte=%d blok=%d gevuld=%d isleeg=%c\n", oBuf.lengte(), oBuf.blok(), oBuf.gevuld(), oBuf.isLeeg() ? 'j' : 'n');

  // Afsluiten
  printf("\nAfgesloten :-)\n\n");

  return 0;
};