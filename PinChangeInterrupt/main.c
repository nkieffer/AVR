#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <inttypes.h>
volatile uint8_t pinb = 0xff;
volatile uint16_t analog = 0x0000;

volatile void (*fpt)(void);

void interrupt1(){
  PORTB ^= _BV(PB3);
}

void interrupt2(){
  PORTB ^= _BV(PB4);
}

ISR(PCINT0_vect){
  uint8_t changed = PINB ^ pinb;
  pinb = PINB;
  PORTB = _BV(PB0) | _BV(PB1);
  if(~(PINB & _BV(PB0)) & (changed & _BV(PB0)))
    fpt = &interrupt1;
  if(~(PINB & _BV(PB1)) & (changed & _BV(PB1)))
    fpt = &interrupt2;
}

ISR(ADC_vect){
  analog = (ADCH << 8) | ADCL;
}
int main(void){
  fpt = &interrupt1;
  DDRB |= _BV(PB4) | _BV(PB3);
  DDRB &= ~_BV(PB0);
  DDRB &= ~_BV(PB1);
  PORTB |= _BV(PB0) | _BV(PB1);
  GIMSK |= _BV(PCIE);
  PCMSK |= _BV(PCINT0) | _BV(PCINT1);
  ADMUX |= _BV(MUX0); //ADC1
  ADCSRA |= _BV(ADEN) | _BV(ADATE) | _BV(ADIE);
  DIDR0 |= _BV(ADC1D);
  sei();
  ADCSRA |= _BV(ADSC);
  while(1){
    (*fpt)();
    uint16_t i = 0;
    while(i < analog){
      _delay_ms(1);
      i+=2;
    }
  }
}
