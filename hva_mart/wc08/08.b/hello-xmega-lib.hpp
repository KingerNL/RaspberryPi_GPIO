#ifndef _HELLO_XMEGA_LIB_HPP_
#define _HELLO_XMEGA_LIB_HPP_

  #include <stdio.h>
  #include <string.h>
  #include <fcntl.h>
  #include <errno.h>
  #include <termios.h>
  #include <unistd.h>
  
  #include <stdbool.h>
  #include <stdint.h>
  #include <stdlib.h>	

  bool InitXmegaSerial(char* pTtyAcm, int nBaudrate, int nParity);
  bool XmegaReadByte(uint8_t* nByte);
  bool XmegaWriteByte(uint8_t* nByte);
  bool CloseXmegaSerial();

#endif // _HELLO_XMEGA_LIB_HPP_
