// 3.c runtime

/* 
Voorbeeld van de taal:

label x
led rood on
wait 100
led rood off
wait 100
jump x
*/

#ifndef _RUNTIME_HPP_
#define _RUNTIME_HPP_

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <string>
#include <vector>
#include "parser.hpp"

class Runtime {
public:
    Runtime();

    ~Runtime();

    bool knop(const std::string &sNaam);

    void led(const std::string &sNaam, bool bStatus);

    void label(const std::string &sNaam);

    void jump(const std::string &sNaam);

    void wait(uint16_t nMSec);

    void run(std::vector <Parser> & lines);
private:
    long findLabel(std::vector <Parser> & lines, const std::string & label);
};

#endif // _RUNTIME_HPP_