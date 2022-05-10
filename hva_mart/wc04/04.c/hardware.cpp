
bool Led::LedStaat(){
    if (bcm2835_gpio_lev(PINLED) == HIGH){
        printf("De Led staat uit")
    }
    if (bcm2835_gpio_lev(PINLED) == LOW){
        printf("De Led staat aan")
    }
}

void Led::VerranderLed(char* Wachttijd){
    bcm2835_delay(Wachttijd);

    if (bcm2835_gpio_lev(PINLED) == HIGH){
        bcm2835_gpio_write(PINLED, LOW);
    }
    if (bcm2835_gpio_lev(PINLED) == LOW){
        bcm2835_gpio_write(PINLED, HIGH);
    }
}

bool Knop::KnopStaat(){
    if (bcm2835_gpio_lev(PINBTN) == HIGH){
        printf("De knop staat uit")
    }
    if (bcm2835_gpio_lev(PINBTN) == LOW){
        printf("De knop staat aan")
    }
}

bool RGBLed::RGBLedStaat(){
    if (bcm2835_gpio_lev(PINRGBLed) == HIGH){
        printf("De RGBLed staat uit")
    }
    if (bcm2835_gpio_lev(PINRGBLed) == LOW){
        printf("De RGBLed staat aan")
    }
}

void RGBLed::VerranderRGBLed(char* Wachttijd){
    bcm2835_delay(Wachttijd);

    if (bcm2835_gpio_lev(PINRGBLed) == HIGH){
        bcm2835_gpio_write(PINRGBLed, LOW);
    }
    if (bcm2835_gpio_lev(PINRGBLed) == LOW){
        bcm2835_gpio_write(PINRGBLed, HIGH);
    }
}