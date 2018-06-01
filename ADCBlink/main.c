#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>
#include <avr/interrupt.h>
volatile uint8_t blinkA = 0;
volatile uint8_t blinkB = 0;
uint8_t spd = 255;
ISR(TIMER0_COMPA_vect){
  blinkA = 1;
}
ISR(TIMER0_COMPB_vect){
  blinkB = 1;
}
int main(void){
  DDRB |= _BV(PB0) | _BV(PB1);
  DDRB &= ~_BV(PB3) | ~_BV(PB2);
  PORTB |=_BV(PB0);
  TCCR0A |= _BV(COM0A0) | _BV(COM0B0) | _BV(WGM01);
  TCCR0B |=  _BV(CS02) | _BV(CS00);
  TIMSK |= _BV(OCIE0A) |_BV(OCIE0B);
  sei();
  OCR0A = 200;//spd;//spd;
  OCR0B = 100;//spd - 126;//255 - spd;
  while(1){
    if (blinkA == 1){
      PORTB ^= _BV(PB0);
      blinkA = 0;
    }
    if(blinkB == 1){
      PORTB ^= _BV(PB1);
      blinkB = 0;
    }
  }
}
