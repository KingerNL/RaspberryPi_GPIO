#ifndef _PLAYER_HPP_
#define _PLAYER_HPP_

#include <ncurses.h>
#include <string>
#include <cstdlib>

using namespace std;

class Player {
  public:
    Player(WINDOW * win, int yc, int xc, char c);

    void mvup();
    void mvdown();
    void mvleft();
    void mvright();
    int  getmv();
    void display();
  private:
  
    int x, y, width, height;
    char character;
    WINDOW * curwin;
};

#endif