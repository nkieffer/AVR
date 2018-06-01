#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>
#include <avr/interrupt.h>

volatile uint8_t brightness = 126;

int main(void){
  uint8_t duty;
  DDRB |= _BV(PB0);
  TCCR0B |= _BV(WGM02);
  TCCR0B |= _BV(CS01) | _BV(CS00);
  TCCR0A |= _BV(WGM00) | _BV(COM0A1);// | _BV(COM0A0);
  OCR0A = brightness;
  while(true){
    OCR0A = brightness;
  }
} 

