#include <avr/io.h>
#include <avr/interrupt.h>
#include <inttypes.h>
#warning This is broken
//uint8_t latched;
ISR(INT0_vect){
  //  latched = !latched;
  PORTB = PORTB & _BV(PB3) ?
    PORTB & ~_BV(PB3) : 
    PORTB | _BV(PB3);
}

void setup(void){
  DDRB |= _BV(PB3); //PB3 output
  DDRB &= ~_BV(PB1); //PB1 input (no pulllup resistor)
  GIMSK |= _BV(INT0); //enable external interrupt
  //latched = 0;
  //MCUCR |= _BV(ISC00) | _BV(ISC01); //rising edge
  MCUCR |= _BV(ISC01); //falling edge
  sei();//enable all interrupts
}

void loop(void){
  //PORTB = latched ? PORTB | _BV(PB3) : PORTB & ~_BV(PB3);
}

int main(void){
  setup();
  while(1) loop();
}
