// 5.b hwdriver

//TODO: zorg voor de juiste 2 #-commando's
#ifndef _KNOP_HPP_
#define _KNOP_HPP_

  #include <bcm2835.h>
  #include <stdbool.h>
  #include <stdio.h>

  // De drukknop class
  class Knop {
    public:
      Knop();
      ~Knop();
      void init(int nPin);
      bool pushed();

    private:
      int nPin_;
  };

#endif // _KNOP_HPP_