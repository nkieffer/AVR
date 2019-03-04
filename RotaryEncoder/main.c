#include <avr/io.h>
#include <avr/interrupt.h>
#include <inttypes.h>
#include <util/delay.h>
uint8_t lastState = 0xff;
volatile uint8_t ct = 9;
ISR(PCINT0_vect){
  uint8_t changed = PINB ^ lastState;
  uint8_t pb3c = (changed & _BV(PB3)) ? 0x1 : 0x0;
  uint8_t pb4c = (changed & _BV(PB4)) ? 0x1 : 0x0;
  uint8_t pb3s = ~(PINB & _BV(PB3)) ? 0x1 : 0x0;
  uint8_t pb4s = ~(PINB & _BV(PB4)) ? 0x1 : 0x0;
  uint8_t pb3l = lastState & _BV(PB3) ? 0x1: 0x0;
  uint8_t pb4l = lastState & _BV(PB4) ? 0x1: 0x0;
  lastState = PINB;
  if(pb4c & pb4l & pb3s)
    ct++;//PORTB ^= _BV(PB1);
  if(pb3c & pb3l & pb4s)
    ct--;//PORTB ^= _BV(PB0);
  /*  if(~(PINB & _BV(PB3)) & (changed & _BV(PB3)))
    PORTB ^= _BV(PB1);
  if(~(PINB & _BV(PB4)) & (changed & _BV(PB4)))
    PORTB ^= _BV(PB0);
  */
}

int main(void){
  DDRB |= _BV(PB0) | _BV(PB1);
  DDRB &= ~_BV(PB3);
  DDRB &= ~_BV(PB4);
  PORTB |= _BV(PB3) | _BV(PB4);
  GIMSK |= _BV(PCIE);
  PCMSK |= _BV(PCINT3) | _BV(PCINT4);
  sei();
  while(1){
    if(ct < 10){
      PORTB |= _BV(PB0);
      // PORTB &= ~_BV(PB1);
    }else{
      //PORTB |= _BV(PB1);
      PORTB &= ~_BV(PB0);
    }
  }
}
