#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
volatile uint16_t analog = 0;
ISR(TIM0_COMPA_vect){
  PORTB ^= _BV(PB3);
}

ISR(ADC_vect){
  analog = ((ADCH << 8) |  ADCL);
  // PORTB ^= _BV(PB4);
}
void setup(void){
  ADMUX |= _BV(MUX0);
  ADCSRA = _BV(ADEN) | _BV(ADATE) | _BV(ADIE);
  DIDR0 |= _BV(ADC1D);
  DDRB |= _BV(PB4) | _BV(PB3);
  PORTB = _BV(PB3);
  TCCR0A = _BV(WGM01);
  TCCR0B = _BV(CS02) | _BV(CS00);
  TIMSK0 |= _BV(OCIE0A);
  sei();
  ADCSRA |= _BV(ADSC);
  OCR0A = 0;
}

void loop(void){
  OCR0A = 255 - (uint8_t)((analog / 1023.0) * 255.0);
}

int main(void){
  setup();
  while(1) loop();
}
