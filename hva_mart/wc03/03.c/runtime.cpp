// 3.c runtime

#include "runtime.hpp"

Runtime::Runtime() {

};

Runtime::~Runtime() {

};

bool Runtime::knop(char* sNaam) {

  printf(" KNOP %s= \n", sNaam);
  return false;
};

void Runtime::led(char* sNaam, bool bStatus) {

  printf(" LED %s %s \n", sNaam, (bStatus ? "on" : "off"));
};

void Runtime::label(char* sNaam) {

  printf(" LABEL %s \n", sNaam);
};

void Runtime::jump(char* sNaam) {

  printf(" JUMP %s \n", sNaam);
};

void Runtime::wait(uint16_t nMSec) {

  printf(" WAIT %d \n", nMSec);
};
