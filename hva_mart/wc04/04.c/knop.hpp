#ifndef _KNOP_HPP_
#define _KNOP_HPP_

#define KNOP_MAX_TOKENS 10
#define KNOP_MAX_TOKENSSIZE 50

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <cstring>
#include <vector>
#include <string>
#include <bcm2835.h>

class Knop {
public:
    Knop();

    ~Knop();

    bool KnopStaat();

private:
};

#endif // _KNOP_HPP_