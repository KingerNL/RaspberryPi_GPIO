
#include "osthread.hpp"

#ifndef _ProgThread_HPP_
#define _ProgThread_HPP_


 
  // De OS thread hardware laag class
  class ProgThread {
    public:  
      ProgThread();
      ~ProgThread();
      void start();
      void stop();
      void LEDProg();
      void DCProg();
      static void* PThread(void *ptr);
      std::string name;
      bool staat = 0;
      FILE *File;
      pthread_t thread_id;

    private:
      Led oLed1_;
      Led oLed2_;
      Led oLed3_;
      
      Knop KnopStopProg;
      Knop KnopStopOS;
      Knop KnopToggle;
      Knop Knopswitch;

      pthread_attr_t oAttr_;
  };

#endif // 