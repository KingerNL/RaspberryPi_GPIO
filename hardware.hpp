// GPIO:  5V 5V  G 14 15 18  G 23  24  G 25 08 07 IDSC  G 12  G 16 20 21
//       X-------------------------------------------------------------- 
// Pin :   2  4  6  8 10 12 14 16  18 20 22 24 26   28 30 32 34 36 38 40
// Pin :   1  3  5  7  9 11 13 15  17 19 21 23 25   27 29 31 33 35 37 39
//       --------------------------------------------------------------- 
// GPIO: 3V3 02 03 04  G 17 27 22 3V3 10 09 11  G IDSD 05 06 13 19 26  G

#ifndef _HARDWARE_HPP_
#define _HARDWARE_HPP_
#define MAX_INVOER 100
#define LED_MAX_TOKENS 10
#define LED_MAX_TOKENSSIZE 50
  
// define Led, Button and DC motor pins
#define PINLEDG RPI_BPLUS_GPIO_J8_11
#define PINLEDY RPI_BPLUS_GPIO_J8_13
#define PINLEDR RPI_BPLUS_GPIO_J8_15
#define PINBTN RPI_BPLUS_GPIO_J8_10
#define DC1 RPI_BPLUS_GPIO_J8_16
#define DC2 RPI_BPLUS_GPIO_J8_18

void initHard();
void initPars();
void Afsluiten();
void DCaan();

class Led {
 public:
  Led();
  ~Led();
  bool LedStaat();
  void VerranderLed();

  private:
};

class Knop {
 public:
  Knop();
  ~Knop();
  bool KnopStaat();

 private:
};

#endif // _HARDWARE_HPP_