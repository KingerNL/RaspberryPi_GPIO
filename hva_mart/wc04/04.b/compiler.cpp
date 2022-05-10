// 3.c runtime
//
// g++ -Wall -o runtime compiler.cpp parser.cpp runtime.cpp
// ./runtime

#include <stdio.h>
#include <stdlib.h>
#include "parser.hpp"
#include "runtime.hpp"

#define MAX_INVOER 100

int main(int nArgc, char *aArgv[]) {

    Runtime oRuntime;
    FILE *pFile;

    char sBuffer[MAX_INVOER + 1];

    // Initialiseren
    printf("03.c runtime\n\n");

    pFile = fopen("myfile.txt", "r");
    // Vraag om een regel tekst in sBuffer
    // Lees een regel

    std::vector <Parser> lines;

    while (fgets(sBuffer, MAX_INVOER, pFile)) {
        printf("\nGelezen: [%s]\n\n\n", sBuffer);

        // Parse de regel in tokens
        lines.emplace_back();
        Parser &lineParser = lines.back();
        size_t nCount = lineParser.parse(sBuffer);

        // Toon de tokens
        printf("Tokens %d: ", nCount);
        for (uint8_t i = 0; i < nCount; i++) {
            printf("{%s}", lineParser.token(i).c_str());
        }
        printf("\n");
        sBuffer[0] = 0;
    }

    fclose(pFile);
    printf("Done reading file, starting the runtime\n");

    oRuntime.run(lines);
//    auto index = oRuntime.findLabel(lines, "duh");
//    printf("index was: %d\n", index);

    // Afsluiten
    printf("\nAfgesloten :-)\n\n");
    return 0;
};