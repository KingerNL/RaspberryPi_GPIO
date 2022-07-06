// 7.c lookuptable

#ifndef _MIJNSINUS_HPP_
#define _MIJNSINUS_HPP_

  #include <stdbool.h>
  #include <stdio.h>
  #include <stdint.h>
  #include <string.h>
  #include <math.h>

  // De lut sinus class
  class Mijnsinus {
    public:
      Mijnsinus(uint16_t nAantalX, uint16_t nAantalY, uint8_t nDecimalen = 3);
      ~Mijnsinus();
      uint16_t aantalX();
      //TODO: voek de [] operator toe
      int16_t operator[](uint16_t nIndex);

    private:
      uint16_t nAantalX_;
      uint16_t nAantalY_;
      int16_t *pBuffer_;
  };

#endif // _MIJNSINUS_HPP_