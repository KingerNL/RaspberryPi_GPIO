#ifndef _RGBLED_HPP_
#define _RGBLED_HPP_

#define RGBLED_MAX_TOKENS 10
#define RGBLED_MAX_TOKENSSIZE 50

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <cstring>
#include <vector>
#include <string>
#include <bcm2835.h>

class RGBLed {
public:
    RGBLed();

    ~RGBLed();

    bool RGBLedStaat();

    void VerranderRGBLed(char* Wachttijd);

private:
};

#endif // _RGBLED_HPP_