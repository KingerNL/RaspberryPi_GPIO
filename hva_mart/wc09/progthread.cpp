
#include "progthread.hpp"
using namespace std;



ProgThread::ProgThread(){
  KnopStopOS.init(RPI_BPLUS_GPIO_J8_08);
  KnopStopProg.init(RPI_BPLUS_GPIO_J8_18);

  KnopToggle.init(RPI_BPLUS_GPIO_J8_38);
  Knopswitch.init(RPI_BPLUS_GPIO_J8_40);

  oLed1_.init(RPI_BPLUS_GPIO_J8_11);
  oLed2_.init(RPI_BPLUS_GPIO_J8_15);
  oLed3_.init(RPI_BPLUS_GPIO_J8_13);

  // DC1.init(RPI_BPLUS_GPIO_J8_16);
  // DC2.init(RPI_BPLUS_GPIO_J8_18);
}

ProgThread::~ProgThread(){
    oLed1_.off();
    oLed2_.off();
    oLed3_.off();
}

void ProgThread::start(){
    
    // Check of staat uit is, en dan maak de thread. Om zo te voorkomen dat je meerdere threads maakt.
    if (staat == 0){
        pthread_attr_init(&oAttr_);
        pthread_attr_setdetachstate(&oAttr_, PTHREAD_CREATE_JOINABLE);

        // Maak de thread zelf en koppel de class instantie via het dataveld
        pthread_create(&thread_id, NULL, &ProgThread::PThread, (void*)(this) ); 
        staat = 1;        
    }

}

void ProgThread::stop(){
    // check of staat daadwerkelijk aan is, en dan join de thread.
    if (staat == 1){
        pthread_join(thread_id, NULL); 
        staat = 0;
    }

}

void* ProgThread::PThread(void *ptr){
    
    ProgThread *pThis;
    pThis = (ProgThread*)ptr;
    while (1) {
        if (pThis->KnopStopProg.pushed() || pThis->KnopStopOS.pushed()) break;
        
        else if (pThis->KnopToggle.pushed()){
            pThis->oLed1_.on();
        }
    }
    return 0;
}

void ProgThread::LEDProg(){
    oLed1_.on();
    oLed2_.on();
}

void ProgThread::DCProg(){
    oLed3_.on();
}