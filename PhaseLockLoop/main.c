#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>
#include <avr/interrupt.h>
volatile uint8_t tct;
volatile double freq = 0.1;//001;
volatile uint16_t analog = 0;
ISR(TIMER1_COMPA_vect){
  PORTB ^= _BV(PB4);
}

ISR(ADC_vect){
  analog = ((ADCH << 8) | ADCL);
}

void loop(void){
  while(1){
    freq = analog / 1023.0 * 0.2612;
    tct = (16000000/ (1 << ((TCCR1 & 15) - 1)) * freq);
    OCR1C = tct;
    OCR1A = tct;
  }
}

int main(void){
  DDRB |=_BV(PB4);
  DDRB &= ~_BV(PB3);
  PORTB = 0;
  PLLCSR |= _BV(PLLE);
  PLLCSR |= _BV(PCKE);

  ADCSRB |= _BV(ACME);
  ADCSRA |= _BV(ADEN) | _BV(ADATE) | _BV(ADIE);
  ADMUX |= _BV(MUX1) | _BV(MUX0);
  DIDR0 |= _BV(ADC3D);
  
  cli();
  TCCR1 |= _BV(CTC1);
  TCCR1 |= _BV(CS13) | _BV(CS12) | _BV(CS11) |_BV(CS10);
  TCNT1 = 0;
  tct = (16000000/ (1 << ((TCCR1 & 15) - 1)) * freq);
  OCR1C = tct;
  OCR1A = tct;
  TIMSK |= _BV(OCIE1A);
  sei();

  ADCSRA |= _BV(ADSC);
  loop();
}

