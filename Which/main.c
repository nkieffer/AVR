#include <avr/interrupt.h>
#include <stdbool.h>
#define MOMENTARYW
volatile uint8_t pins;

ISR(PCINT0_vect){
  pins = PINB & (_BV(PB1) | _BV(PB2));
}
int main(void){
  DDRB |= _BV(PB0) | _BV(PB4);
  DDRB &= ~(_BV(PB2) | _BV(PB1));
  PORTB |= _BV(PB2) | _BV(PB1);
  PORTB |= _BV(PB0) | _BV(PB4);
  PCMSK |= _BV(PB1) | _BV(PB2);
  GIMSK |= _BV(PCIE);
  sei();
  while(true){
#ifdef MOMENTARY 
    PORTB &= ~(_BV(PB0) | _BV(PB4));
#endif
    if((pins & _BV(PB1)) == 0){
      PORTB |= _BV(PB4);
      PORTB &= ~_BV(PB0);
    }
    if ((pins & _BV(PB2)) == 0){
      PORTB &= ~_BV(PB4);
      PORTB |= _BV(PB0);
    }	
  }
}
