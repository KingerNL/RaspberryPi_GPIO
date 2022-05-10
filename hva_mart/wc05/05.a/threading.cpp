// 5.a multithreading
//
// g++ -Wall -thread -o multithreading multithreading.cpp threadletters.cpp threadoptellen.cpp
// g++ -pthread -o threading threading.cpp
// ./threading

//TODO: juiste include toevoegen
#include "multithreading.hpp"

int main(){
  std::thread worker1(ThreadOptellen);
  std::thread worker2(ThreadLetters);

  worker1.join();
  worker2.join();
}