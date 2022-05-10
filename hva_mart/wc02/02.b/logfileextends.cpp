// 2.b logfileextends
//
// g++ -Wall -o logfileextends logfileextends.cpp logfile.cpp binfile.cpp file.cpp
// ./logfileextends

#include <stdio.h>
#include "logfile.hpp"
#include "binfile.hpp"

int main(int nArgc, char* aArgv[]) {

  Logfile oLog1;
  Binfile oBin1;
  char sBuf[100];

  // Initialiseren
  printf("02.b logfileextends\n\n");
  if (!oLog1.open("log1.txt")) {
    printf("Fout: de logfile kon niet geopend worden!");
    printf("\nAfgebroken :(\n\n");
  };
  if (!oBin1.open("log1.dat")) {
    printf("Fout: de logfile kon niet geopend worden!");
    printf("\nAfgebroken :(\n\n");
  };

  // Maak 1000 keer
  for (int i = 0; i < 1000; i++) {
    //TODO #3: wijzig de tekst i kwadraad te tonen
    sprintf(sBuf, "[%d] ", i);

    printf(sBuf);
    oLog1.write(i);
    oLog1.write(sBuf);
    oLog1 >> sBuf;

    oBin1.write(i);
  };

  // Afsluiten
  oLog1.close();
  oBin1.close();
  printf("\nAfgesloten :-)\n\n");
  return 0;
};