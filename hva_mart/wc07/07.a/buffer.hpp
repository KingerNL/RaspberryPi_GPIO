// 7.a cyclischbuffer

#ifndef _BUFFER_HPP_
#define _BUFFER_HPP_

  #include <stdbool.h>
  #include <stdio.h>

  // De cyclische buffer class
  class Buffer {
    public:
      Buffer(unsigned char nLengte, unsigned char nBlok = 1);
      ~Buffer();
      unsigned char lengte();
      unsigned char blok();
      unsigned char gevuld();
      bool isLeeg();
      void push(unsigned char nData);
      unsigned char pull();

    private:
      unsigned char nLengte_;
      unsigned char nBlok_;
      unsigned char *pBuffer_;
      unsigned int nKop_;
      unsigned int nStaart_;
  };


#endif 