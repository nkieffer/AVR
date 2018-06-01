#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>
#include <avr/interrupt.h>

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
