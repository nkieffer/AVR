#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>
#include <avr/interrupt.h>
volatile int8_t dir = 1;
volatile uint8_t duty = 126;
volatile uint16_t analog = 0;
uint8_t level;
ISR(ADC_vect){
  analog = ((ADCH << 8)|ADCL);//ADC High and low bits
}

int main(void){
  DDRB |= _BV(PB0) | _BV(PB4);
  DDRB &= ~_BV(PB3);
  GTCCR |= _BV(PWM1B) | _BV(COM1B0);
  TCCR1 |= 1;
  OCR1C = 0xFF;
  OCR1A = 0;//255;//255 - 10;
  OCR1B = 0;//255 - 245;
  TCCR1 |= _BV(COM1A0) | _BV(PWM1A);
  
  //ADTS[2:0] = 0: free running mode
  //ADCSRB |= _BV(ACME); //Analog comparator multiplexer enabled
  //ADEN: ADC Enable
  //ADATE: ADC Auto Trigger Enable
  //ADIE: ADC Interrupt Enable
  ADCSRA |= _BV(ADEN) | _BV(ADATE) | _BV(ADIE);
  ADMUX |= _BV(MUX1) | _BV(MUX0); //ADC3 (PB3)
  DIDR0 |= _BV(ADC2D); // Digital input disable on ADC2
  sei();
  ADCSRA |= _BV(ADSC);//ADSC: ADC Start Conversion
  while(1){
    level = 255 - (uint8_t)((analog / 1023.0) * 255.0);
    OCR1A = level;//duty;
    OCR1B = 0;//level;//ADCL |  / 1023 * 255;//255 - duty;//10;//duty/2;
  }
}
