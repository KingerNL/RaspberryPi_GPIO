#ifndef _LED_HPP_
#define _LED_HPP_

#define LED_MAX_TOKENS 10
#define LED_MAX_TOKENSSIZE 50

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <cstring>
#include <vector>
#include <string>
#include <bcm2835.h>

// Blink on RPi big connector J8 pin 10 which is GPIO pin 15
#define PINLED RPI_BPLUS_GPIO_J8_10

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



#endif // _LED_HPP_