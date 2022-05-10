//
// Include de library's
#include "windows.hpp"
#include "parser.hpp"
#include "runtime.hpp"
#include "hardware.hpp"

Runtime::Runtime() {

};

Runtime::~Runtime() {

};

// Runned de code in een loop totdat de knop wordt ingedrukt
void Runtime::run(std::vector <Parser> &lines) {
    
 for (size_t i = 0; i < lines.size(); i++) {
 
  Parser &oParser = lines[i];
  size_t nCount = oParser.getNumberOfTokens();

  // Voer de ingelezen commando's uit
  if (nCount > 0) {
   if (oParser.token(0) == "knop") {
    // Goed commando?
    if (nCount == 2) {
     bRet = knop(oParser.token(1));
     if (bRet == 1){
      break;
     }
    } else {
     printf(" Syntax error! ");
     break;
    };
   } 
   
   else if (oParser.token(0) == "led") {
    // Goed commando?
    if (nCount == 3) {
     led(oParser.token(1), oParser.token(2) == "on");
    } else {
     printf(" Syntax error! ");
     break;
    };
   } 
   
   else if (oParser.token(0) == "label") {
    // Goed commando?
    if (nCount == 2) {
     label(oParser.token(1));
    } else {
     printf(" Syntax error! ");
     break;
    };
   } 
    
   else if (oParser.token(0) == "jump") {
    if (nCount == 2) {
     long newIndex = findLabel(lines, oParser.token(1));
     if (newIndex < 0) {
      printf(" Syntax error!, can't find label %s ", oParser.token(1).c_str());
      break;
     } else {
      i = newIndex;
     }
     } else {
      printf(" Syntax error! ");
      break;
     };
    } 
    
   else if (oParser.token(0) == "wait") {
    // Goed commando?
    if (nCount == 2) {
     wait(atoi(oParser.token(1).c_str()));
    } else {
     printf(" Syntax error! ");
     break;
    };
   } 
    
   else {
    printf(" Onbekende invoer! ");
    break;
   };
  }
 }
}

// Runned als de parsed bij knop komt
bool Runtime::knop(const std::string &sNaam) {
 Knop oKnop;
 Kstaat = oKnop.KnopStaat();
 return Kstaat;
};

// Runned als de parsed bij led komt
void Runtime::led(const std::string &sNaam, bool bStatus) {
 Led oLed;
 oLed.VerranderLed();
}; 

// Runned als de parsed bij label komt
void Runtime::label(const std::string &sNaam) {
};

// Runned als de parsed bij jump komt
void Runtime::jump(const std::string &sNaam) {
};

// Runned als de parsed bij wait komt
void Runtime::wait(uint16_t nMSec) {
 bcm2835_delay(nMSec);
};

// Vind de label en jump naar de label toe.
long Runtime::findLabel(std::vector <Parser> &lines, const std::string &label) {
 for (size_t i = 0; i < lines.size(); i++) {
  Parser &oParser = lines[i];
  size_t nCount = oParser.getNumberOfTokens();
  if (oParser.token(0) == "label") {
   // Goed commando?
   if (nCount == 2 && oParser.token(1) == label) {
    return i;
   }
  }
 }
 return -1;
}