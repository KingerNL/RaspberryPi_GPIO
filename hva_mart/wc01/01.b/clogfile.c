// 1.b clogfile
//
// gcc -Wall -o clogfile clogfile.c logfile.c
// ./clogfile

#include <stdio.h>
#include "logfile.h"

int main() {
  char buffer[200]; // Buffer to store data
  FILE * stream;
  stream = fopen("log1.txt", "r");
  int count = fread(&buffer, sizeof(char), 100, stream);
  fclose(stream);
  // Printing data to check validity
  printf("%s \n", buffer);
  printf("Elements read: %d \n", count);
  return 0;
}
