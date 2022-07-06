
#ifndef _HARDWARE_HPP_
#define _HARDWARE_HPP_

#define LED_MAX_TOKENS 10
#define LED_MAX_TOKENSSIZE 50

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <cstring>
#include <vector>
#include <string>
#include <bcm2835.h>

// De drukknop class
class Knop {
public:
    Knop();
    ~Knop();
    void init(int nPin);
    bool pushed();

private:
    int nPin_;
};

class Led {
    public:
        Led();
        ~Led();
        void VerranderLed();
        void init(int nPin);
        void on();
        void off();

    private:
        int nPin_;
};

class DC {
    public:
        DC();
        ~DC();
        void init(int nPin1, int nPin2);
        void DCaan();
        void DCuit();

    private:
        int nPin1_;
        int nPin2_;
};

#endif // _KNOP_HPP_