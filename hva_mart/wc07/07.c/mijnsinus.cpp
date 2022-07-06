// 7.c lookuptable

#include "mijnsinus.hpp"

Mijnsinus::Mijnsinus(uint16_t nAantalX, uint16_t nAantalY, uint8_t nDecimalen) {

  uint16_t i;
  double fSchaalX = M_PI * 2.0 / (double)nAantalX;
  double fSchaalY = nAantalY;
  double fDecimalen = 1.0;

  // Onthoud de instellingen en alloceer het geheugen
  nAantalX_ = nAantalX;
  nAantalY_ = nAantalY;
  pBuffer_ = new int16_t[nAantalX_];
  
  // Bepaal de decimalen factor
  for (i = 0; i < nDecimalen; i++) {
    fDecimalen *= 10.0;
  };

  // Vul de buffer met de sinus waarden
  for (i = 0; i < nAantalX_; i++) {
    // 2*Pi => nAantalX
    pBuffer_[i] = fSchaalY * sin(fSchaalX * i) * fDecimalen;
  };
};

Mijnsinus::~Mijnsinus() {

  // Geheugen vrijgeven
  delete[] pBuffer_;
};

uint16_t Mijnsinus::aantalX() {

  return nAantalX_;
};

int16_t Mijnsinus::operator[](uint16_t nIndex) {

  return pBuffer_[nIndex];
};