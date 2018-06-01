#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>
#include <avr/interrupt.h>
#include "power_down.h"
#define COUNT 0;
#define FLASH 1;
volatile bool start = false;
volatile bool stop = false;
volatile uint8_t count = 0;
volatile uint8_t mode = 0;
void initINT0(void){
  MCUCR |= _BV(ISC00) | _BV(ISC01);
  GIMSK |= _BV(INT0);
}

ISR(INT0_vect){
  cli();
  TCNT1 = 0;
  count++;
  sei();
}

ISR(TIMER1_COMPA_vect){
  if(mode == 0){
    mode = 1;
    OCR1C = 13;
    OCR1A = 13;
    PORTB ^= _BV(PB0);
    count--;
  }else{
    PORTB ^= _BV(PB0);
    count--;
  }
}

int main(void){
  check_power_down();
  DDRB &= ~_BV(PB2);
  DDRB |= _BV(PB0);
  PORTB &= ~_BV(PB0);
  initINT0();

  TCNT1 = 0;
  TCCR1 |= _BV(CTC1);
  TCCR1 |= _BV(CS13) | _BV(CS12) | _BV(CS11);
  OCR1C = 0xff;
  OCR1A = 0xff;		     
  TIMSK |= _BV(OCIE1A);

  sei();
  while(true){
    if(count <= 0){
      PORTB &= ~_BV(PB0);
      mode = 0;
      cli();
      OCR1C = 0xff;
      OCR1A = 0xff;
      TCNT1 = 0;
      sei();
    }
  }
}
