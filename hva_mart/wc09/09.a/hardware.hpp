// GPIO:  5V 5V  G 14 15 18  G 23  24  G 25 08 07 IDSC  G 12  G 16 20 21
//       X-------------------------------------------------------------- 
// Pin :   2  4  6  8 10 12 14 16  18 20 22 24 26   28 30 32 34 36 38 40
// Pin :   1  3  5  7  9 11 13 15  17 19 21 23 25   27 29 31 33 35 37 39
//       --------------------------------------------------------------- 
// GPIO: 3V3 02 03 04  G 17 27 22 3V3 10 09 11  G IDSD 05 06 13 19 26  G

#ifndef _HARDWARE_HPP_
#define _HARDWARE_HPP_

#define LED_MAX_TOKENS 10
#define LED_MAX_TOKENSSIZE 50
  
// Blink on RPi big connector J8 pin 10 which is GPIO pin 15
#define PINLED RPI_BPLUS_GPIO_J8_10

// Stop on RPi big connector J8 pin 12 which is GPIO pin 18
#define PINBTN RPI_BPLUS_GPIO_J8_12

void VerranderLed(); //Probeer deze in de class Led te krijgen, met runtime actie

class Led {
public:
    Led();
    ~Led();
    bool LedStaat();
private:
};

class Knop {
public:
    Knop();
    ~Knop();
    bool KnopStaat();

private:
};

class RGBLed {
public:
    RGBLed();
    ~RGBLed();
    bool RGBLedStaat();
    void VerranderRGBLed(char* Wachttijd);

private:
};

#endif // _HARDWARE_HPP_