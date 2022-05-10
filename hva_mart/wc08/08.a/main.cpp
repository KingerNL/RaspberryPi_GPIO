/*
 * 8.a uncaps
 */ 

#ifndef F_CPU
#define F_CPU 2000000UL
#endif

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include "serialF0.h"

int main(void) {
  
  uint16_t nData;

  // Initialiseer en test de rode LED
  PORTF.DIRSET = PIN1_bm;
  PORTF.OUTSET = PIN1_bm;
  _delay_ms(500);
  PORTF.OUTCLR = PIN1_bm;
  _delay_ms(250);

  // Init the PORT F0 for UART (options: BAUD_38K4 or BAUD_57K6 or BAUD_115K2)
  init_stream(F_CPU, BAUD_115K2);
  sei();

  // Blijf luisteren en reageren
  while (1) {

    PORTF.OUTSET = PIN1_bm;
    while ((nData = uartF0_getc()) == UART_NO_DATA) {};
    //printf("%c ", nData);
    if ('A' <= nData && nData <= 'Z') {
      nData = nData + ('a' - 'A');
    }
    else if ('a' <= nData && nData <= 'z') {
      nData = nData - ('a' - 'A');
    }
    else if ('0' <= nData && nData <= '9') {
      nData = '9' - nData + '0';
    };
    uartF0_putc(nData);

    PORTF.OUTCLR = PIN1_bm;
    _delay_ms(250);
  };

  return 0;
};