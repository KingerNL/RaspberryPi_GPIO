
#include "progthread.hpp"
using namespace std;

// Initialiseer alle benodigde hardware
ProgThread::ProgThread(){
  KnopStopOS.init(RPI_BPLUS_GPIO_J8_08);
  KnopStopProg.init(RPI_BPLUS_GPIO_J8_18);

  KnopToggle.init(RPI_BPLUS_GPIO_J8_40);
  Knopswitch.init(RPI_BPLUS_GPIO_J8_38);

  oLed1_.init(RPI_BPLUS_GPIO_J8_11);
  oLed2_.init(RPI_BPLUS_GPIO_J8_13);
  oLed3_.init(RPI_BPLUS_GPIO_J8_15);

  oLedDC1_.init(RPI_BPLUS_GPIO_J8_31);
  oLedDC2_.init(RPI_BPLUS_GPIO_J8_32);
  oLedDC1_.on();

  DC1.init(RPI_BPLUS_GPIO_J8_35);
  DC2.init(RPI_BPLUS_GPIO_J8_36);
}

// Zet laatste LED ook uit
ProgThread::~ProgThread(){
    oLedDC1_.off();
}

// Start een thread. Indien deze staat nog niet aan staat. 
void ProgThread::start(std::string naam){
    
    // Check of staat uit is, en dan maak de thread. Om zo te voorkomen dat je meerdere threads maakt.
    if (staat == 0){
        pthread_attr_init(&oAttr_);
        pthread_attr_setdetachstate(&oAttr_, PTHREAD_CREATE_JOINABLE);

        // Maak de thread zelf en koppel de class instantie via het dataveld
        pthread_create(&thread_id, NULL, &ProgThread::PThread, (void*)(this) ); 
        staat = 1;
    }

}

// Join de thread weer.
void ProgThread::stop(std::string naam){
    // check of staat daadwerkelijk aan is, en dan join de thread.
    if (staat == 1){
        if (naam == "LEDS"){
            oLed1_.off();
            oLed2_.off();
            oLed3_.off();
        }
        if (naam == "DC-MOTOR"){
            DC1.DCuit();
            oLedDC1_.on();
            oLedDC2_.off();
        }
        pthread_join(thread_id, NULL); 
        staat = 0;
    }

}

// Run de verschillende threads
void* ProgThread::PThread(void *ptr){
    
    ProgThread *pThis;
    pThis = (ProgThread*)ptr;
    
    if (pThis->name == "LEDS"){
        while (1) {
            //Run LEDS prog
            if (pThis->KnopStopProg.pushed() || pThis->KnopStopOS.pushed()) break;
        }
    }
    else if (pThis->name == "DC-MOTOR") {
        while (1) {
            //Run DC Progs
            if (pThis->KnopStopProg.pushed() || pThis->KnopStopOS.pushed()) break;
        }
    }
    else {
        while (1) {
            // Run .txt prog
            if (pThis->KnopStopProg.pushed() || pThis->KnopStopOS.pushed()) break;
        }
    }
    return 0;
}

// Verrander LED indien Window gelijk is aan 1,2 of 3.
void ProgThread::LEDProg(int LEDWin_){
    if (LEDWin_ == 1){
        oLed1_.VerranderLed();
    }
    if (LEDWin_ == 2){
        oLed2_.VerranderLed();
    }
    if (LEDWin_ == 0){
        oLed3_.VerranderLed();
    }
}   

// Doe DC-MOTOR aan
void ProgThread::DCaan(){
    DC1.DCaan();
    DC2.DCuit();
    oLedDC2_.on();
    oLedDC1_.off();
}

// Doe DC-MOTOR uit
void ProgThread::DCuit(){
    DC1.DCuit();
    DC2.DCuit();
    oLedDC1_.on();
    oLedDC2_.off();

}