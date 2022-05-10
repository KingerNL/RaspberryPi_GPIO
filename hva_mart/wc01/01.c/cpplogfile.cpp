// 1.c cpplogfile
//
// g++ -Wall -o cpplogfile cpplogfile.cpp logfile.cpp
// ./cpplogfile

#include <stdio.h>
#include "logfile.hpp"

int main(int nArgc, char* aArgv[]) {

  //TODO #3: voeg een tweede logbestand toe voor andere gegevens
  Logfile oLog1;
  char sBuf[100];

  // Initialiseren
  printf("01.c cpplogfile\n\n");
  oLog1.open("File.txt");

  // Maak 1000 keer
  for (int i = 0; i < 10; i++) {
    //TODO #2: wijzig de tekst i kwadraad te tonen
    sprintf(sBuf, "%d ", i*i);
    oLog1.write(sBuf); // Print/Write naar de oLog1 file aka "file_01.c.txt"
  };
  oLog1.read(sBuf);

  // Afsluiten
  oLog1.close();
  return 0;
};