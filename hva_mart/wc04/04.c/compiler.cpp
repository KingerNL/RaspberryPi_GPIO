// 3.c runtime
//
// g++ -Wall -o runtime compiler.cpp parser.cpp runtime.cpp led.cpp -lbcm2835
// ./runtime

#include <stdio.h>
#include <stdlib.h>
#include "parser.hpp"
#include "runtime.hpp"
#include "led.hpp"
#include "knop.hpp"
#include "rgbled.hpp"

#define MAX_INVOER 100

int main(int nArgc, char *aArgv[]) {
    
    if (!bcm2835_init()){
        return 1;
    }

    bcm2835_gpio_fsel(PINLED, BCM2835_GPIO_FSEL_OUTP);

    Runtime oRuntime;
    FILE *pFile;
    
    char sBuffer[MAX_INVOER + 1];

    // Initialiseren
    printf("03.c runtime\n\n");

    pFile = fopen("mijntaal.txt", "r");
    // Vraag om een regel tekst in sBuffer
    // Lees een regel

    std::vector <Parser> lines;

    while (fgets(sBuffer, MAX_INVOER, pFile)) {
        printf("\nGelezen: %s", sBuffer);

        // Parse de regel in tokens
        lines.emplace_back();
        Parser &lineParser = lines.back();
        size_t nCount = lineParser.parse(sBuffer);

        sBuffer[0] = 0;
    }

    fclose(pFile);
    printf("\n\nDone reading file, starting the runtime\n\n");

    oRuntime.run(lines);

    // Afsluiten
    printf("\nAfgesloten :-)\n\n");
    return 0;
};