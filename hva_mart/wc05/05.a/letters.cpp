// 5.a multithreading

#include "multithreading.hpp"

void ThreadLetters() {
  while(1){
    for(int b = 0; b < 100; b++ ){
      std::cout << "-";
    }
  }
}