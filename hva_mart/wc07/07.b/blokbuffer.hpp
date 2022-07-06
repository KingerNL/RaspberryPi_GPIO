// 7.b paging

#ifndef _BLOKBUFFER_HPP_
#define _BLOKBUFFER_HPP_

  #include <stdbool.h>
  #include <stdio.h>
  #include <string.h>

  // De pagina buffer class
  class Blokbuffer {
    public:
      Blokbuffer(unsigned int nLengte, unsigned int nBlok);
      ~Blokbuffer();
      unsigned int lengte();
      unsigned int blok();
      bool isLeeg();
      bool isVol();
      bool isVrij(unsigned int nIndex);
      //TODO: zorg dat functies isVol() en isVrij public beschikbaar zijn
      void maakVrij(unsigned int nIndex);
      unsigned int toevoegen(void* pData, unsigned int nData, unsigned int *nIndex);
      void *operator[](unsigned int nIndex);

    private:
      unsigned int nLengte_;
      unsigned int nBlok_;
      unsigned char *pBuffer_;
      bool *pBufferVrij_;
  };

#endif // _BLOKBUFFER_HPP_