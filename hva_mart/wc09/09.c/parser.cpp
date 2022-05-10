// 3.b compiler

#include "parser.hpp"
#include "windows.hpp"

Parser::Parser() {

    // Maak de tokens leeg
    //memset(aToken_, 0, PARSER_MAX_TOKENS * PARSER_MAX_TOKENSSIZE);
};

Parser::~Parser() {

};

//TODO: zorg dat de spatie ook als witruimte wordt gezien
static bool isWhiteSpace(char character) {
    return character == '\t' || character == ' ' || character == '\n' || character == '\r';
}

uint8_t Parser::parse(char *sLine) {

    uint8_t nTokens = 0;
    uint16_t nIndex = 0, t = 0;

    // Loop alle tekens langs tot \0
    while (sLine[nIndex] != 0) {

        // Sla witruimte over: tab, spatie en enter
        while (sLine[nIndex] > 0 && isWhiteSpace(sLine[nIndex])) {
            nIndex++;
        };

        // Lees en sla op tot het einde van sLine of tot de eerste witruimte
        t = 0;
        while (sLine[nIndex] > 0 && !isWhiteSpace(sLine[nIndex])) {
            if (t == 0) {
                aToken_.emplace_back("");
            }
            aToken_[nTokens] += sLine[nIndex];
            t++;
            nIndex++;
        };

        // Echt een token gelezen?
        if (t > 0) {
            // Sluit de string af
//      aToken_[nTokens][t] = 0;
            nTokens++;
        };
    };

    return nTokens;
};

std::string &Parser::token(uint8_t nIndex) {
    if (nIndex >= getNumberOfTokens()) {
        nIndex = getNumberOfTokens() - 1;
    }
    return aToken_[nIndex];
};

void Parser::clear() {
    aToken_.clear();
}

size_t Parser::getNumberOfTokens() {
    return aToken_.size();
}
