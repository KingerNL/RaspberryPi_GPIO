// 1.c cpplogfile

#include "logfile.hpp"

bool Logfile::open(const char* sFilename) {

  // Open de logfile om aan toe te voegen.
  pFile_ = fopen(sFilename, "a");

  return pFile_ != NULL;
};

bool Logfile::close() {

  // Sluit het bestand (0 = succes)
  return fclose(pFile_) == 0;
};

void Logfile::write(char* pBuf) {

  char sNewline[] = "\n";

  // Schrijf alle letters.
  while (*pBuf > 0) {
    fputc(*pBuf, pFile_);
    pBuf++;
  };

  // Sluit af met \n
  pBuf = sNewline;
  while (*pBuf > 0) {
    fputc(*pBuf, pFile_);
    pBuf++;
  };
};

void Logfile::read(char* pBuf) {

  int result = fread(pBuf, 1, 100, pFile_);

  printf("%s \n", pBuf);
  printf("Elements read: %d \n", result);
};