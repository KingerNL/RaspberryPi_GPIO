// 7.b paging

#include "blokbuffer.hpp"

Blokbuffer::Blokbuffer(unsigned int nLengte, unsigned int nBlok) {

  // Onthoud de instellingen en alloceer het geheugen
  nLengte_ = nLengte;
  nBlok_ = nBlok;
  pBuffer_ = new unsigned char[nLengte_ * nBlok_];
  //TODO: alloceer C++ stijl een array van nLengte_ lang en type bool
  pBufferVrij_ = new bool[nLengte_];
  memset(pBufferVrij_, true, nLengte_);
};

Blokbuffer::~Blokbuffer() {

  // Geheugen vrijgeven
  delete[] pBuffer_;
  delete[] pBufferVrij_;
};

unsigned int Blokbuffer::lengte() {

  return nLengte_;
};

unsigned int Blokbuffer::blok() {

  return nBlok_;
};

bool Blokbuffer::isLeeg() {

  for (unsigned int i = 0; i < nLengte_; i++) {
    if (!pBufferVrij_[i]) {
      return false;
    };
  };

  return true;
};

bool Blokbuffer::isVol() {

  for (unsigned int i = 0; i < nLengte_; i++) {
    if (pBufferVrij_[i]) {
      return false;
    };
  };

  return true;
};

bool Blokbuffer::isVrij(unsigned int nIndex) {

  return pBufferVrij_[nIndex];
};

void Blokbuffer::maakVrij(unsigned int nIndex) {

  pBufferVrij_[nIndex] = true;
};

unsigned int Blokbuffer::toevoegen(void* pData, unsigned int nData, unsigned int *nIndex) {

  // Zoek een vrije index
  *nIndex = 0;
  while (*nIndex < nLengte_ && !pBufferVrij_[*nIndex]) {
    (*nIndex)++;
  };
  if (*nIndex == nLengte_) {
    return 0;
  }

  // Kopieer de nieuwe data met max van nBlok_
  nData = nData < nBlok_ ? nData : nBlok_;
  memcpy(&pBuffer_[(*nIndex) * nBlok_], pData, nData);
  
  // Markeer bezet
  pBufferVrij_[*nIndex] = false;

  return nData;
};

void *Blokbuffer::operator[](unsigned int nIndex) {

  return &pBuffer_[nIndex * nBlok_];
};

