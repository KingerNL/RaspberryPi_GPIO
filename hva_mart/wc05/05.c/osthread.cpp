// GPIO:  5V 5V  G 14 15 18  G 23  24  G 25 08 07 IDSC  G 12  G 16 20 21
//       X-------------------------------------------------------------- 
// Pin :   2  4  6  8 10 12 14 16  18 20 22 24 26   28 30 32 34 36 38 40
// Pin :   1  3  5  7  9 11 13 15  17 19 21 23 25   27 29 31 33 35 37 39
//       --------------------------------------------------------------- 
// GPIO: 3V3 02 03 04  G 17 27 22 3V3 10 09 11  G IDSD 05 06 13 19 26  G

// 5.c hwlayer

#include "osthread.hpp"

OsThread::OsThread() {
  
  // Initialiseer de hardwarelaag voordat hij gebruikt gaat worden
  //TODO: kies bijvoorbeeld knoppen pin 15 en 16, en LED's pin 11 en 13
  oHwStop_.init(RPI_BPLUS_GPIO_J8_10);
  oHwKnop_.init(RPI_BPLUS_GPIO_J8_12);
  oLed1_.init(RPI_BPLUS_GPIO_J8_11);
  oLed2_.init(RPI_BPLUS_GPIO_J8_15);

  // Initialiseer de thread instellingen
  pthread_attr_init(&oAttr_);
  pthread_attr_setdetachstate(&oAttr_, PTHREAD_CREATE_JOINABLE);

  // Maak de thread zelf en koppel de class instantie via het dataveld
  int nRet = pthread_create(&oThread_, &oAttr_, thread, (void*)this);
};

OsThread::~OsThread() {

  // Vrijgeven thread instellingen
  pthread_attr_destroy(&oAttr_);
};

void OsThread::join() {

  void *pStatus;

  // Wacht tot de thread klaar is
  pthread_join(oThread_, &pStatus); 
};

void OsThread::delay(long nMSec) {

  struct timespec oTime, oTimeLeft;

  // Handige delay-functie in msec
  oTime.tv_sec = 0; 
  oTime.tv_nsec = nMSec * 1000000L;
  nanosleep(&oTime, &oTimeLeft);
};

void *OsThread::thread(void *pThreadData) {

  OsThread *pThis;
  bool bLed1;

  // Maak een referentie naar het class object
  pThis = (OsThread*)pThreadData;

  // Start met LED1
  bLed1 = true;
  pThis->oLed1_.on();

  // Ga door tot drukknop 1
  while (true) {

    // Toon unieke thread tekst
    printf("."); 
    fflush(stdout);
    
    pThis->delay(400);

    // Wisselen?
    if (pThis->oHwKnop_.pushed()) {
      bLed1 = !bLed1;
      if (bLed1) {
        pThis->oLed1_.on();
        pThis->oLed2_.off();
      }
      else {
        pThis->oLed1_.off();
        pThis->oLed2_.on();
      }
    };

    // Stoppen?
    if (pThis->oHwStop_.pushed()) {
      pThis->oLed1_.off();
      pThis->oLed2_.off();
      pthread_exit(NULL);
    };
  };
 
  // Thread vrijgeven
  pthread_exit(NULL);
};
