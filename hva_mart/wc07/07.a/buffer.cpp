// 7.a cyclischbuffer

#include "buffer.hpp"

Buffer::Buffer(unsigned char nLengte, unsigned char nBlok) {

  // Onthoud de instellingen en alloceer het geheugen
  nLengte_ = nLengte;
  nBlok_ = nBlok;
  nKop_ = 0;
  nStaart_ = 0;
  pBuffer_ = new unsigned char[(unsigned int)nLengte_ * (unsigned int)nBlok_];
};

Buffer::~Buffer() {

  // Geheugen vrijgeven
  delete[] pBuffer_;
};

unsigned char Buffer::lengte() {

  return nLengte_;
};

unsigned char Buffer::blok() {

  return nBlok_;
};

unsigned char Buffer::gevuld() {

  // Geef het verschil van de ko en staart aanwijzers
  //TODO: zorg dat het resultaat hieronder gelijk wordt aan het return-type
  return int(nKop_ <= nStaart_ ? nStaart_ - nKop_ : nKop_ - nStaart_);
};

bool Buffer::isLeeg() {

  return nKop_ == nStaart_;
};

void Buffer::push(unsigned char nData) {

  // Forceer altijd opslaan
  pBuffer_[nKop_] = nData;
  nKop_ = (nKop_ + 1) % nLengte_;
  if (nKop_ == nStaart_) {
    nStaart_ = (nStaart_ + 1) % nLengte_;
  };
};

unsigned char Buffer::pull() {

  unsigned char nData = pBuffer_[nStaart_];

  // Opvragen alleen zinnig indien niet leeg
  if (!isLeeg()) {
    nStaart_ = (nStaart_ + 1) % nLengte_;  
  };

  return nData;
};
