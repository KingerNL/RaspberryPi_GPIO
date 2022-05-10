// 3.b compiler
//
// g++ -Wall -o compiler compiler.cpp parser.cpp
// ./compiler

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <cstring>
#include "parser.hpp"

#define MAX_INVOER 100

int main(int nArgc, char* aArgv[]) {

  Parser oParser;
  char sBuffer[MAX_INVOER + 1];
  uint8_t nCount;

  // Initialiseren
  printf("03.b compiler\n\n");
  
  // Vraag om een regel tekst in sBuffer
  while (strcmp(sBuffer, "\n") != 0){
    // Lees een regel
    printf("\nCommandoinvoer: ");
    fgets(sBuffer, MAX_INVOER, stdin);
    printf("Gelezen: [%s]\n", sBuffer);

    // Parse de regel in tokens
    nCount = oParser.parse(sBuffer);
    printf("Tokens %d: ", nCount);
    
    for (uint8_t i = 0; i < nCount; i++) {
      printf("{%s}", oParser.token(i));
    };
    printf("\n");
    
  };

  // Afsluiten
  printf("\nAfgesloten :-)\n\n");
  return 0;
};