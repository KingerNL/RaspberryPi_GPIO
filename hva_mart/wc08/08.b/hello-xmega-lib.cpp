#include "hello-xmega-lib.hpp"

int _nSerial = 0;

bool InitXmegaSerial(char* pTtyAcm, int nBaudrate, int nParity) {

  struct termios oTty;

  // A possible string?
  if (pTtyAcm == NULL) {
		printf("No valid device name!\n");
		return false; 
  }

  // Try to open the serial connection
  printf("[%s] ", pTtyAcm);
  _nSerial = open(pTtyAcm, O_RDWR | O_NOCTTY | O_NONBLOCK);
	if (_nSerial == 0)
	{
		perror(pTtyAcm);
		printf("Failed to open device: %s\n", pTtyAcm);
		return false; 
	}

  // Clear struct to start with new settings
  memset(&oTty, 0, sizeof(oTty));
  if (tcgetattr(_nSerial, &oTty) != 0) {
    printf("Error %i getting settings: %s\n", errno, strerror(errno));
    return false;
  };

  // Init minimal serial settings for noncannonical mode (no extra character processing)
  oTty.c_iflag = 0; // Input
  oTty.c_oflag = 0; // Output
  oTty.c_lflag = 0; // Line
  oTty.c_cflag = CS8 | CREAD | CLOCAL; // Character
  oTty.c_cc[VMIN] = 1; // Length
  oTty.c_cc[VTIME] = 0; // Timeout

  // Init speed: use default constants
  if (cfsetispeed(&oTty, nBaudrate) < 0) {
    printf("Error %i setting input speed: %s\n", errno, strerror(errno));
    return false;
  };
  if (cfsetospeed(&oTty, nBaudrate) < 0) {
    printf("Error %i setting output speed: %s\n", errno, strerror(errno));
    return false;
  };

  // Set new settings NOW
  if (tcsetattr(_nSerial, TCSANOW, &oTty) < 0) {
    printf("Error %i setting settings: %s\n", errno, strerror(errno));
    return false;
  };
  
  // Flush input and output buffers
  if (tcflush(_nSerial, TCIOFLUSH) < 0) {
    printf("Error %i flushing input and output: %s\n", errno, strerror(errno));
    return false;
  };

  return true;
};

bool XmegaReadByte(uint8_t* nByte) {

  ssize_t nSize;

  // Check for valid open connection
  if (_nSerial == 0) {
    return false;
  }

  // Read one byte only
  nSize = read(_nSerial, nByte, 1);
  if (nSize == -1 && errno == 11) {
    return false;
  }
  if (nSize == 0) {
    return false;
  }

  if (nSize == -1) {
    printf("Error reading: %s", strerror(errno));
    return false;
  }

  return true;
};

bool XmegaWriteByte(uint8_t* nByte) {

  ssize_t nSize;

  // Check for valid open connection
  if (_nSerial == 0) {
    return false;
  }

  // Read one byte only
  nSize = write(_nSerial, nByte, 1);
  if (nSize != 1) {
    return false;
  };

  return true;
};

bool CloseXmegaSerial() {

  if (_nSerial != 0) {
    close(_nSerial);
  }

  return true;
};