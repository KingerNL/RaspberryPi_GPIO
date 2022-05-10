#include <string.h>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


//std::vector <std::string> oScript;

int main(int nArgc, char* aArgv[]) {

    std::vector <string> v;

    for(int i = 1; i < nArgc; i++) {
        FILE * pFile = fopen(aArgv[i], "r");

        if (pFile!=NULL) {
            v.push_back(aArgv[i]);
        }
    }

    for (std::string i: v){
        std::cout << i << " ";
    }
}
