// 3.b compiler

#ifndef _PARSER_HPP_
#define _PARSER_HPP_

#define PARSER_MAX_TOKENS 10
#define PARSER_MAX_TOKENSSIZE 50

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <cstring>
#include <vector>
#include <string>

class Parser {
public:
    Parser();

    ~Parser();

    uint8_t parse(char *sLine);

    std::string &token(uint8_t nIndex);

    void clear();

    size_t getNumberOfTokens();

private:
//    char aToken_[PARSER_MAX_TOKENS][PARSER_MAX_TOKENSSIZE];
    std::vector<std::string> aToken_;
};

#endif // _PARSER_HPP_