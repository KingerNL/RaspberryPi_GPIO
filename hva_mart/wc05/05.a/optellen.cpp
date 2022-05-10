// 5.a multithreading

#include "multithreading.hpp"

int a;
 
void ThreadOptellen() {
  while(1){
    for(a = 0; a < 100; a++ ){
      std::cout << a;
    }
    a == 0;
  }
}