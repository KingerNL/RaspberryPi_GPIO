// 2.a logfileoverload
//
// g++ -Wall -o logfileoverload logfileoverload.cpp logfile.cpp
// ./logfileoverload

#include <stdio.h>
#include "logfile.hpp"

int main(int nArgc, char* aArgv[]) {

  //TODO #3: voeg een tweede logbestand toe voor andere gegevens
  Logfile oLog1;
  char sBuf[100];

  // Initialiseren
  printf("02.a logfileoverload\n\n");
  if (!oLog1.open("log1.txt")) {
    printf("Fout: de logfile kon niet geopend worden!");
    printf("\nAfgebroken :(\n\n");
  };

  // Maak 1000 keer
  for (int i = 0; i < 1000; i++) {
    //TODO #2: wijzig de tekst i kwadraad te tonen
    sprintf(sBuf, "[%d] ", i);

    printf(sBuf);
    oLog1.write(i);
    oLog1.write(sBuf);
    oLog1 >> sBuf;
  };

  // Afsluiten
  oLog1.close();
  printf("\nAfgesloten :-)\n\n");
  return 0;
};