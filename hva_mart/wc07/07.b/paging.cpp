// 7.b paging
//
// g++ -Wall -o paging paging.cpp blokbuffer.cpp
// ./paging

#include "paging.hpp"

int main(int nArgc, char* aArgv[]) {

  char sTekst1[] = "Hallo blok buffer";
  char sTekst2[] = "De tweede tekst";
  char sTekst3[] = "Op de eerste index?";
  unsigned int nIndex1, nIndex2, nIndex3;

  // Initialiseren
  printf("7.b paging\n\n");
  //TODO: maak variabele oBlok van type Blokbuffer van 10 lang en blokformaat 128
  Blokbuffer oBlok(10, 128);
  
  printf("> lengte=%d blok=%d isleeg=%c isvol=%c\n", oBlok.lengte(), oBlok.blok(), oBlok.isLeeg() ? 'j' : 'n', oBlok.isVol() ? 'j' : 'n');

  // Voeg eerste tekst data toe: zal index 0 zijn
  oBlok.toevoegen(sTekst1, strlen(sTekst1), &nIndex1);
  printf("> %d = [%s]\n", nIndex1, (unsigned char*)oBlok[nIndex1]);

  // Voeg tweede tekst data toe: zal index 1 zijn
  oBlok.toevoegen(sTekst2, strlen(sTekst2), &nIndex2);
  printf("> %d = [%s]\n", nIndex2, (unsigned char*)oBlok[nIndex2]);

  // Voeg derde tekst data toe: zal index 0 zijn
  oBlok.maakVrij(0);
  oBlok.toevoegen(sTekst3, strlen(sTekst3), &nIndex3);
  printf("> %d = [%s]\n", nIndex3, (unsigned char*)oBlok[nIndex3]);

  // Afsluiten
  printf("> lengte=%d blok=%d isleeg=%c isvol=%c\n", oBlok.lengte(), oBlok.blok(), oBlok.isLeeg() ? 'j' : 'n', oBlok.isVol() ? 'j' : 'n');
  printf("\nAfgesloten :-)\n\n");

  return 0;
};
