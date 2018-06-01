#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>
#include <avr/interrupt.h>
ISR(ANA_COMP_vect){
  PORTB ^= _BV(PB4);
}
int main(void){
  DDRB |=_BV(PB4);
  PORTB = 0;
  ACSR |= _BV(ACIS1);// | _BV(ACIS0); //set behavior of
  ACSR |= _BV(ACIE);
  DIDR0 |= _BV(AIN1D) | _BV(AIN0D);
  sei();
  while(1){
  }
}
