// 3.b compiler

#include "parser.hpp"
#include <cstring>
#include <iostream>

Parser::Parser() {

  // Maak de tokens leeg
  memset(aToken_, 0, PARSER_MAX_TOKENS * PARSER_MAX_TOKENSSIZE);
};

Parser::~Parser() {

};

uint8_t Parser::parse(char* sLine) {

  uint8_t nTokens = 0;
  uint16_t nIndex = 0, t = 0;
  
  // Loop alle tekens langs tot \0
  while (sLine[nIndex] != 0) {

    // Sla witruimte over: tab, spatie en enter
    //TODO: zorg dat de spatie ook als witruimte wordt gezien
    while (sLine[nIndex] > 0 && (sLine[nIndex] == '\t' || sLine[nIndex] == ' ' || sLine[nIndex] == '\n' || sLine[nIndex] == '\r')) {
      nIndex++;
    };

    // Lees en sla op tot het einde van sLine of tot de eerste witruimte
    t = 0;
    //TODO: zorg dat de spatie ook als witruimte wordt gezien
    while (sLine[nIndex] > 0 && sLine[nIndex] != '\t' && sLine[nIndex] != ' ' && sLine[nIndex] != '\n' && sLine[nIndex] != '\r') {
      aToken_[nTokens][t] = sLine[nIndex];
      t++; nIndex++;
    };

    // Echt een token gelezen?
    if (t > 0) {
      // Sluit de string af
      aToken_[nTokens][t] = 0;
      nTokens++;
    };
  };

  return nTokens;
};

char* Parser::token(uint8_t nIndex) {

  if (nIndex >= PARSER_MAX_TOKENS) {
    nIndex = 0;
  };
  return aToken_[nIndex];
};
