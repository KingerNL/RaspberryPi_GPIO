
#ifndef _RUNTIME_HPP_
#define _RUNTIME_HPP_

#include "windows.hpp"
#include "parser.hpp"


class Runtime {
public:

 Runtime();
 ~Runtime();
 bool knop(const std::string &sNaam);
 void led(const std::string &sNaam, bool bStatus);
 void label(const std::string &sNaam);
 void jump(const std::string &sNaam);
 void wait(uint16_t nMSec);
 void run(std::vector <Parser> & lines);
 bool bRet;
 bool Kstaat;

private:
 long findLabel(std::vector <Parser> & lines, const std::string & label);
};

#endif // _RUNTIME_HPP_