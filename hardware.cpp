
#include "windows.hpp"
#include "parser.hpp"
#include "runtime.hpp"
#include "hardware.hpp"

void DCaan(){
 
 // Laat DC motor draaien totdat de button wordt ingedrukt
 while (bcm2835_gpio_lev(PINBTN) == HIGH) { 
  bcm2835_gpio_write(PINLEDG, HIGH);
  bcm2835_gpio_write(DC1, HIGH);
  bcm2835_gpio_write(DC2, LOW);
 }; 

 bcm2835_gpio_write(PINLEDG, LOW);
 bcm2835_gpio_write(DC1, LOW);
 bcm2835_gpio_write(DC2, LOW);

}

void initHard(){

 // Initaliseer Led, Button & CD motor pins
 bcm2835_gpio_fsel(PINLEDR, BCM2835_GPIO_FSEL_OUTP);
 bcm2835_gpio_fsel(PINLEDY, BCM2835_GPIO_FSEL_OUTP);
 bcm2835_gpio_fsel(PINLEDG, BCM2835_GPIO_FSEL_OUTP);
 bcm2835_gpio_fsel(PINBTN, BCM2835_GPIO_FSEL_INPT);
 bcm2835_gpio_set_pud(PINBTN, BCM2835_GPIO_PUD_UP);
 bcm2835_gpio_fsel(DC1, BCM2835_GPIO_FSEL_OUTP);
 bcm2835_gpio_fsel(DC2, BCM2835_GPIO_FSEL_OUTP);

 bcm2835_gpio_write(PINLEDR, HIGH);
 bcm2835_delay(2000);
 bcm2835_gpio_write(PINLEDR, LOW);
}

// Initaliseer de Parser, en lees de .txt file uit
void initPars(){

 Runtime oRuntime;
 FILE *pFile;
 char sBuffer[MAX_INVOER + 1];
 pFile = fopen("mijntaal.txt", "r");

 // Lees een regel
 std::vector <Parser> lines;
 
 // Leest alle regels uit, Parsed deze in tokens, en noemt deze sBuffer.
 while (fgets(sBuffer, MAX_INVOER, pFile)) {
    
  lines.emplace_back();
  Parser &lineParser = lines.back();
  lineParser.parse(sBuffer);
  sBuffer[0] = 0;

 };

 fclose(pFile);
 oRuntime.run(lines);

};

// LED COMMANDO'S
Led::Led(){

}

Led::~Led(){
    
}

bool Led::LedStaat(){

 if (bcm2835_gpio_lev(PINLEDR) == HIGH) {
  printf("De Led staat uit");
  return false;
 }
 
 if (bcm2835_gpio_lev(PINLEDR) == LOW) {
  printf("De Led staat aan"); 
  return true;
 }
 
 else {
  return "Error, geen Led staat";
 }
}

void Led::VerranderLed(){

 if (bcm2835_gpio_lev(PINLEDY) == LOW) {
  bcm2835_gpio_write(PINLEDY, HIGH);
 }

 else if (bcm2835_gpio_lev(PINLEDY) == HIGH) {
  bcm2835_gpio_write(PINLEDY, LOW);
 }
    
};

// KNOP COMMANDO'S
Knop::Knop(){
    
}

Knop::~Knop(){

}

bool Knop::KnopStaat(){
 
 if (bcm2835_gpio_lev(PINBTN) == HIGH){
  return false;
 }
 
 else if (bcm2835_gpio_lev(PINBTN) == LOW){
  return true;
 }
 
 else {
  return "Error, geen knop staat";
 }
}