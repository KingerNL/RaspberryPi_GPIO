// 1.b clogfile

#include "logfile.h"

FILE* logfile_open(char* sFilename) {

  // Open de logfile om aan toe te voegen.
  return fopen(sFilename, "a");
};

bool logfile_close(FILE *pFile) {

  // Sluit het bestand (0 = succes)
  return fclose(pFile) == 0;
};

void logfile_write(FILE *pFile, char* pBuf) {

  char sNewline[] = "\n";

  // Schrijf alle letters.
  while (*pBuf > 0) {
    fputc(*pBuf, pFile);
    pBuf++;
  };

  // Sluit af met \n
  pBuf = sNewline;
  while (*pBuf > 0) {
    fputc(*pBuf, pFile);
    pBuf++;
  };
};
