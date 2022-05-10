// 2.a logfileoverload

#include "logfile.hpp"
#include <stdio.h>


Logfile::Logfile() {

  // Initialiseer de private variabelen
  pFile_ = NULL;
};

Logfile::~Logfile() {

  // Zorg altijd voor goed opruimen/vrijgeven!
  if (pFile_ != NULL) {
    close();
  };
};

bool Logfile::open(const char* sFilename) {
};

bool Logfile::close() {

  int nRet;

  // Sluit het bestand (0 = succes)
  nRet = fclose(pFile_);
  pFile_ = NULL;
  return nRet == 0;
};

void Logfile::write(int nValue) {

  char sNumber[50], *pBuf;

  // Schrijf alle cijfers en een \n.
  sprintf(sNumber, "%d\n", nValue);
  pBuf = sNumber;
  while (*pBuf > 0) {
    fputc(*pBuf, pFile_);
    pBuf++;
  };
};

void Logfile::write(char* pBuf) {
};

void Logfile::operator>>(char* pBuf) {

  write(pBuf);
};