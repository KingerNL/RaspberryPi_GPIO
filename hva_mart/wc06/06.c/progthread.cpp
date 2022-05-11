
#include "progthread.hpp"
using namespace std;



ProgThread::ProgThread(){
  oLed1_.init(RPI_BPLUS_GPIO_J8_11);
  oLed2_.init(RPI_BPLUS_GPIO_J8_15);
  oLed3_.init(RPI_BPLUS_GPIO_J8_13);
}

ProgThread::~ProgThread(){
    
}

void ProgThread::start(){    
    pthread_create(&thread_id, NULL, test, NULL);   
    staat = 1;
}

void ProgThread::stop(){
    // tijdelijk detach. join kan ook maar omdat void * test() een while 1() loop heeft zal deze nooit returnen
    pthread_detach(thread_id); 
    staat = 0;
}

void* test(void *ptr){
    while (1){
       oLed1_.VerranderLed(); // Kan niet aangezien oLed in de class zit en deze functie zit dat niet.
       delay(500);
    }
    
    return 0;
}