#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>
#include <avr/interrupt.h>
#include <stdlib.h>
uint8_t h = 200;
uint8_t l = 55;
volatile uint8_t r = 0;
volatile uint8_t g = 0;
volatile uint8_t b = 0;
volatile uint8_t inc = 0;
uint8_t ct = 0;
volatile uint8_t seed=0;
ISR(INT0_vect){
  uint8_t t = r;
  r = g;
  g = b;
  b = t;
}

ISR(ADC_vect){
  seed = ADCL;
}

void setupPWM(void){
  TCCR0A |= _BV(WGM00) | _BV(WGM01) | _BV(COM0A1) | _BV(COM0B1);
  TCCR0B |= /*_BV(CS01) |*/ _BV(CS00);
  TCCR1 |= _BV(CS10);
  GTCCR |= _BV(PWM1B) | _BV(COM1B0);  
}

int main(void){
  ADCSRA |= (1 << ADEN) | (1 << ADIE);
  ADCSRA |= (1 << ADPS1) | (1 << ADPS0); //prescale ADC for use with temp sensor
  ADMUX |= _BV(MUX0) | _BV(MUX1) | _BV(MUX2) | _BV(MUX3); //select temp sensor
  ADMUX |= _BV(REFS1); // 1.1 volts
  sei();
  ADCSRA |= (1 << ADSC); // start conversion
  while(ADCSRA & (1 << ADSC)); // wait for conversion to finish
  srand(seed);
  ADCSRA &= ~(1 << ADEN);
  uint8_t r = (uint8_t)(rand() % 255);
  uint8_t g = (uint8_t)(rand() % 255);
  uint8_t b = (uint8_t)(rand() % 255);
  uint8_t c1[3] = {r,g,b};//0x00, 0x00, 0X00};
  uint8_t c2[3] = {r/2,g*2,b-r};//(uint8_t)(rand() %255),0x00, 0x00};
  DDRB |= _BV(PB0) | _BV(PB1) | _BV(PB4) | _BV(PB2);
  PORTB |=_BV(PB2);
  MCUCR |= _BV(ISC01) | _BV(ISC00);
  //GIMSK |= _BV(INT0);
  OCR1C = 132; 
  setupPWM();
  sei();
  while(1){
    ct++;
    if(ct % 10 == 0){
      uint8_t t[3] = {c1[0], c1[1], c1[2]};
      c1[0] = c2[1] + 1;
      c1[1] = c2[2] + 1;
      c1[2] = c2[0] - rand();
      c2[0] = t[0] + 3;
      c2[1] = t[1] + 3;
      c2[2] = t[2] + rand();
    }
    OCR0A = c1[0];
    OCR0B = c1[1];
    OCR1B = c1[2];
    _delay_ms(10);
    OCR0A = 0;
    OCR0B = 0;
    OCR1B = 0;
    _delay_ms(1);
    USICR |= _BV(USITC);
    OCR0A = c2[0];
    OCR0B = c2[1];
    OCR1B = c2[2];
    _delay_ms(10);
    OCR0A = 0;
    OCR0B = 0;
    OCR1B = 0;
    _delay_ms(1);
    USICR |= _BV(USITC);
  }
}
