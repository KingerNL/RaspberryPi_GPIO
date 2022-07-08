// GPIO:  5V 5V  G 14 15 18  G 23  24  G 25 08 07 IDSC  G 12  G 16 20 21
//       X-------------------------------------------------------------- 
// Pin :   2  4  6  8 10 12 14 16  18 20 22 24 26   28 30 32 34 36 38 40
// Pin :   1  3  5  7  9 11 13 15  17 19 21 23 25   27 29 31 33 35 37 39
//       --------------------------------------------------------------- 
// GPIO: 3V3 02 03 04  G 17 27 22 3V3 10 09 11  G IDSD 05 06 13 19 26  G

#include "hardware.hpp"
#include <iostream>

//LED

Led::Led(){
}

Led::~Led(){
}

void Led::VerranderLed(){

    if (bcm2835_gpio_lev(nPin_) == HIGH){
        bcm2835_gpio_write(nPin_, LOW);
        return;
    }
    if (bcm2835_gpio_lev(nPin_) == LOW){
        bcm2835_gpio_write(nPin_, HIGH);
        return;
    }
};                      

void Led::init(int nPin) {

  nPin_ = nPin;
  bcm2835_gpio_fsel(nPin_, BCM2835_GPIO_FSEL_OUTP);
};

void Led::on(){
    bcm2835_gpio_write(nPin_, HIGH);
}

void Led::off(){
    bcm2835_gpio_write(nPin_, LOW);
}

// Knop

Knop::Knop() {

};

Knop::~Knop() {

};

void Knop::init(int nPin) {

  nPin_ = nPin;
  bcm2835_gpio_fsel(nPin_, BCM2835_GPIO_FSEL_INPT);
  bcm2835_gpio_set_pud(nPin_, BCM2835_GPIO_PUD_UP);
};

bool Knop::pushed() {

  // Knop ingesteld met pull-up, dus ingedrukt is laag
  return bcm2835_gpio_lev(nPin_) == LOW;
};

// DC motor

DC::DC(){

};

DC::~DC(){

};

void DC::init(int nPin){

  nPin_ = nPin;

  bcm2835_gpio_fsel(nPin_, BCM2835_GPIO_FSEL_OUTP);

};

void DC::DCaan(){
  bcm2835_gpio_write(nPin_, HIGH);
};

void DC::DCuit(){
  bcm2835_gpio_write(nPin_, LOW);
};