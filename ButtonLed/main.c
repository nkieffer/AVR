#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>
#include <avr/interrupt.h>
#include "power_down.h"
volatile bool start = false;
volatile bool stop = false;

void initINT0(void){
  MCUCR |= _BV(ISC00) | _BV(ISC01);
  GIMSK |= _BV(INT0);
  TCCR1 |= 0;
  TIMSK = 0;
}

ISR(INT0_vect){
  start = true;
}

ISR(TIMER1_COMPA_vect){
  stop = true;
}

int main(void){
  check_power_down();
  DDRB &= ~_BV(PB2);
  DDRB |= _BV(PB0);
  PORTB |= _BV(PB0);
  initINT0();
  sei();
  while(true){
    if(start){
      MCUCR = 0;
      GIMSK &= ~_BV(INT0);
      start = false;
      TCNT1 = 0;
      PORTB &= ~_BV(PB0);
      TCCR1 |= _BV(CTC1);
      TCCR1 |= _BV(CS13) | _BV(CS12) | _BV(CS11);
      OCR1C = 0xff;
      OCR1A = 0xff;		     
      TIMSK |= _BV(OCIE1A);
    }
    if(stop){
      stop = false;
      PORTB |= _BV(PB0);
      initINT0();
    }
  }
}
