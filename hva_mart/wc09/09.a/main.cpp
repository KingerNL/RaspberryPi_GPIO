//
// g++ -Wall -pthread -lncurses -o programma main.cpp windows.cpp parser.cpp runtime.cpp hardware.cpp -lbcm2835
//
// ./programma

#include "windows.hpp"
#include "parser.hpp"
#include "runtime.hpp"
#include "hardware.hpp"

#define MAX_INVOER 100
using namespace std;

int main(){

  // Initaliseer de twee windows
  initWin();

  // Maak twee threads aan, beide voor hun eigen window
  std::thread worker2(prntWin2);
  std::thread worker1(prntWin1);
  
    // Init the bcsm2835 library
  if (!bcm2835_init()) {
    return 1;
  };

  // Set the PIN to be output
  bcm2835_gpio_fsel(PINLED, BCM2835_GPIO_FSEL_OUTP);


    Runtime oRuntime;
    FILE *pFile;
    char sBuffer[MAX_INVOER + 1];
    pFile = fopen("mijntaal.txt", "r");
    // Vraag om een regel tekst in sBuffer
    // Lees een regel
    std::vector <Parser> lines;
    while (fgets(sBuffer, MAX_INVOER, pFile)) {

        // Parse de regel in tokens
        lines.emplace_back();
        Parser &lineParser = lines.back();
        size_t nCount = lineParser.parse(sBuffer);

        sBuffer[0] = 0;
    }
    fclose(pFile);
    oRuntime.run(lines);
  

  // Laat main() wachten tot beide threads klaar zijn
  worker1.join();
  worker2.join();

  // Sluit het programma af
  closeWin();  

}
