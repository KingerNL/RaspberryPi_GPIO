
#ifndef _LOGFILE_H_
#define _LOGFILE_H_

#include <stdbool.h>
#include <stdio.h>

FILE* logfile_open(char* sFilename);
bool logfile_close(FILE *pFile);
void logfile_write(FILE *pFile, char* pBuf);  //TODO #1: voeg de logfile 'interface' toe

#endif // _LOGFILE_H_
