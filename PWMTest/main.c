#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>
#include <avr/interrupt.h>
uint8_t h = 200;
uint8_t l = 55;
volatile uint8_t r = 0;
volatile uint8_t g = 0;
volatile uint8_t b = 0;
volatile uint8_t inc = 0;
ISR(INT0_vect){
  uint8_t t = r;
  r = g;
  g = b;
  b = t;
}

void setupPWM(void){
  TCCR0A |= _BV(WGM00) | _BV(WGM01) | _BV(COM0A1) | _BV(COM0B1);
  TCCR0B |= /*_BV(CS01) |*/ _BV(CS00);
  TCCR1 |= _BV(CS10);
  GTCCR |= _BV(PWM1B) | _BV(COM1B0);  
}

int main(void){
  DDRB |= _BV(PB0) | _BV(PB1) | _BV(PB4) | _BV(PB2);
  PORTB |=_BV(PB2);
  MCUCR |= _BV(ISC01) | _BV(ISC00);
  //  GIMSK |= _BV(INT0);
  OCR1C = 132; 
  setupPWM();
  sei();
  while(1){
    for(r = 0; r < 255; r+=1){
      for(g = 0; g < 255; g+=1){
	for(b = 0; b < 255; b+=1){
	  OCR0A = r;
	  OCR0B = g;
	  OCR1B = b;
	  _delay_ms(10);
	  OCR0A = 0;
	  OCR0B = 0;
	  OCR1B = 0;
	  	  _delay_ms(1);
	  USICR |= _BV(USITC);
	  OCR0A = b;
	  OCR0B = r;
	  OCR1B = g;
	  _delay_ms(10);
	  OCR0A = 0;
	  OCR0B = 0;
	  OCR1B = 0;
	  	  _delay_ms(1);
	  USICR |= _BV(USITC);
	}
      }
    }
  }
}