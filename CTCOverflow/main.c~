#include <avr/io.h>
#include <stdbool.h>
#include <avr/interrupt.h>

int main(void){
  DDRB |= _BV(PB0) | _BV(PB4); //set PB0 & PB4 to output
  PORTB |= _BV(PB0); //turn on PB0
  TIMSK |= _BV(OCIE0A); //enable output compare match interrupt
  TCCR0A = (1 << WGM01) | _BV(COM0A0); //set CTC mode for timer0  & set OC0A to toggle on output compare match 
  TCCR0B |= _BV(CS02) | _BV(CS00); //prescaler of 1024
  /*
    _BV(CS00) => 1 no prescale
    _BV(CS01) => 2 clk/8
    _BV(CS01) | _BV(CS00) => 3 clk/64
    _BV(CS02) => 4 clk/256
    _BV(CS02) | _BV(CS00) => 5 clk/1024
  */
  float freq = 16; //minimum frequency obtainable by 8-bit timer
  OCR0A = (F_CPU/(1024.0 * freq))-1;
}
