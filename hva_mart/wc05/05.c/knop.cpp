// 5.b hwdriver

#include "knop.hpp"

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