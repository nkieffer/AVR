#include <avr/io.h>
#include <stdbool.h>
#include <avr/interrupt.h>
volatile uint8_t f = 0;
ISR(TIMER1_OVF_vect){
  PORTB ^= _BV(PB0) | _BV(PB4);
}

int main(void){
  DDRB |= _BV(PB0) | _BV(PB4); //set PB0 & PB4 to output
  PORTB |= _BV(PB0);// | _BV(PB4); //turn on PB0
  TIMSK |= _BV(TOIE1); //enable output compare match interrupt
  sei();
  TCCR1 |= _BV(CS13) | _BV(CS12) | _BV(CS10);// | _BV(CS10); //prescaler of 16384
  while(true); //Infinite loop is necessary to keep the clock ticking.
}
