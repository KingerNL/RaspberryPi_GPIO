
#include "progthread.hpp"
using namespace std;



ProgThread::ProgThread(){

}

ProgThread::~ProgThread(){
    
}

void ProgThread::start(){
    pthread_create(&thread_id, NULL, test, NULL);   
}

void ProgThread::stop(){
    pthread_join(thread_id, NULL);
}

void* test(void *ptr){
    while (1){
    std::cout << "Ola son nachos";
    }
    
    return 0;
}