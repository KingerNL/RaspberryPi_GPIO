// 3.c runtime

#include "runtime.hpp"

Runtime::Runtime() {

};

Runtime::~Runtime() {

};

void Runtime::run(std::vector <Parser> &lines) {
    for (size_t i = 0; i < lines.size(); i++) {

        Parser &oParser = lines[i];
        size_t nCount = oParser.getNumberOfTokens();

        // Voer de ingelezen commando's uit
        if (nCount > 0) {
            if (oParser.token(0) == "knop") {
                // Goed commando?
                if (nCount == 2) {
                    bool bRet = knop(oParser.token(1));
                } else {
                    printf(" Syntax error! ");
                    break;
                };
            } else if (oParser.token(0) == "led") {
                // Goed commando?
                if (nCount == 3) {
                    led(oParser.token(1), oParser.token(2) == "on");
                } else {
                    printf(" Syntax error! ");
                    break;
                };
            } else if (oParser.token(0) == "label") {
                // Goed commando?
                if (nCount == 2) {
                    label(oParser.token(1));
                } else {
                    printf(" Syntax error! ");
                    break;
                };
            } else
                //TODO: voeg commando jump toe (hint: dit is bijna het zelfde als commando label)
            if (oParser.token(0) == "jump") {
                if (nCount == 2) {
//                    jump(oParser.token(1));
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
            } else if (oParser.token(0) == "wait") {
                // Goed commando?
                if (nCount == 2) {
                    wait(atoi(oParser.token(1).c_str()));
                } else {
                    printf(" Syntax error! ");
                    break;
                };
            } else {
                printf(" Onbekende invoer! ");
                break;
            };
        }
        printf("\n");

    }
}

bool Runtime::knop(const std::string &sNaam) {

    printf(" KNOP %s=", sNaam.c_str());
    return false;
};

void Runtime::led(const std::string &sNaam, bool bStatus) {

    printf(" LED %s %s ", sNaam.c_str(), (bStatus ? "on" : "off"));
};

void Runtime::label(const std::string &sNaam) {

    printf(" LABEL %s ", sNaam.c_str());
};

void Runtime::jump(const std::string &sNaam) {

    printf(" JUMP %s ", sNaam.c_str());
};

void Runtime::wait(uint16_t nMSec) {

    printf(" WAIT %d ", nMSec);
};

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