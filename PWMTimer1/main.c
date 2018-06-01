#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>
#include <avr/interrupt.h>
volatile int8_t dir = 1;
volatile uint8_t duty = 1;
ISR(TIMER0_COMPA_vect){
   duty += dir;
}

int main(void){
  DDRB |= _BV(PB0) | _BV(PB4);
  GTCCR |= _BV(PWM1B)  | _BV(COM1B0);
  TCCR1 |= 1;
  OCR1C = 0xFF;
  OCR1A = 255;//255 - 10;
  OCR1B = 0;//255 - 245;
  TCCR1 |= _BV(COM1A0) | _BV(PWM1A);
  
  TCCR0A |= _BV(WGM01);
  TCCR0B |= _BV(CS02) | _BV(CS00);
  TIMSK |= _BV(OCIE0A);
  
  OCR0A = (F_CPU / 1024 * 0.0001);
  sei();
  while(1){
    if(duty >= 255){
      dir = -1;
    }else if (duty <= 0){
      dir = 1;
    }
    OCR1A = duty;
    OCR1B = 255 -duty;//10;//duty/2;
    //   _delay_ms(10);
    //OCR1A = 0;
  }
}
/*
int main(void){
  uint8_t duty;
  uint16_t ct = 0;
  DDRB |= _BV(PB0);
  // TCCR0B |= _BV(WGM02);
  TCCR0B |= _BV(CS01);// | _BV(CS00);
  TCCR0A |= _BV(WGM00) | _BV(COM0A1);// | _BV(COM0A0);
  OCR0A = duty;
  while(true){
    for(duty = 0; duty < 255; duty++){
      OCR0A = duty;
      _delay_ms(10);
    }
    for(;duty > 0; duty--){
      OCR0A = duty;
      _delay_ms(10);
    }
  } 
}
*/
