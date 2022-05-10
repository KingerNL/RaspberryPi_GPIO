
#include "osthread.hpp"

#ifndef _ProgThread_HPP_
#define _ProgThread_HPP_

  void* test(void *ptr);
 
  
  // De OS thread hardware laag class
  class ProgThread {
    public:
        ProgThread();
        ~ProgThread();
        void start();
        void stop();
        std::string name;
        pthread_t thread_id;

    private:
  };

#endif // 