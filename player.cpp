// Deel van code van: https://www.youtube.com/channel/UCwA85g9HuIgg0SSjX59p0YQ
// In playlist: making Snake from ncurses

#include "player.hpp"

Player::Player(WINDOW * win, int yc, int xc, char c) {
 curwin = win;
 y = yc;
 x = xc;
 getmaxyx(curwin, height, width);
 keypad(curwin, true);
 character = c;
}

void Player::mvup() {
 mvwaddch(curwin, y, x, '.');
 y -= 1;
 if (y < 1) {
    y = 1;
 }
}

void Player::mvdown() {
 mvwaddch(curwin, y, x, '.');
 y += 1;
 if(y > 28){
  y = 28;
 }
}

void Player::mvleft() {
 mvwaddch(curwin, y, x, '.');
 x -= 1;
 if(x < 1){
  x = 1;
 }
}

void Player::mvright() {
 mvwaddch(curwin, y, x, '.');
 x += 1;
 if(x > 37){
  x = 37;
 }
}

int Player::getmv() {
 int choice = wgetch(curwin);
 switch(choice) {
  case KEY_UP:
   mvup();
   break;
  case KEY_DOWN:
   mvdown();
   break;
  case KEY_LEFT:
   mvleft();
   break;
   case KEY_RIGHT:
  mvright();
   break;
  default:
   break;
  }
  return choice;
}

void Player::display() {
 mvwaddch(curwin, y, x, character);
}