#include <stdbool.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "rgbled.h"
#define G OCR0A
#define B OCR0B
#define R OCR1B
volatile uint8_t channel = 0;
volatile uint16_t analog = 0;
volatile uint16_t ct = 0;
ISR(INT0_vect){
  channel = 1;//(channel + 1) % 3;
}

ISR(ADC_vect){
  analog = ((ADCH << 8)|ADCL);//ADC High and low bits
}

ISR(TIMER0_OVF_vect){
  // ct++;
}
int main(void){
  RGBLed * active;
  RGBLed leds[8];
  uint8_t i = 0;
  leds[0] = rgbled(255, 0, 0, 0);
  leds[1] = rgbled(0, 255, 0, 1);
  leds[2] = rgbled(0, 0, 255, 2);
  leds[3] = rgbled(255, 255, 0, 3);
  leds[4] = rgbled(0, 255, 255, 4);
  leds[5] = rgbled(255, 0, 255, 5);
  leds[6] = rgbled(255, 255, 255, 6);
  leds[7] = rgbled(0, 0, 0, 7);
  active = leds;
  TIMSK |= _BV(TOIE0);
  // INT0 on falling edge;
  MCUCR |= _BV(ISC01) | _BV(ISC00);
  // Set pins as output;
  DDRB |= _BV(PB0) | _BV(PB1) | _BV(PB4);
  // Set pins as input;
  DDRB &= ~(_BV(PB2) | _BV(PB5));
  // Set pullup resistor
  PORTB |= _BV(PB2);
  // enable external interrupt
  GIMSK |= _BV(INT0);

  /*
   * PWM Settings
   */
  //select CLKIO no prescale
  TCCR0B |= _BV(CS00);
  // Non inverting phase correct PWM mode
  TCCR0A |= _BV(COM0B1) | _BV(COM0A1) | _BV(WGM00);// | _BV(WGM01);
  // CLKIO no prescale
  TCCR1 |= _BV(CS10);
  // enable PWM B
  GTCCR |= _BV(PWM1B) | _BV(COM1B0);
  // set top of timer1
  OCR1C = 0xff;
  

  // enable ADC, Enable ADC Autotrigger, Enable ADC complete interrupt
  ADCSRA |= _BV(ADEN) | _BV(ADATE) | _BV(ADIE);
  // select ADC  channel PB3
  ADMUX |= _BV(MUX1) | _BV(MUX0);
  // disable digital input buffer on PB3
  DIDR0 |= _BV(ADC3D);
  // enable interrupts
  PRR |= _BV(PRUSI);
  PRR &= ~_BV(PRUSI);
  USICR = 0;
  USICR |= _BV(USIOIE);
  sei();
  // start conversion
  ADCSRA |= _BV(ADSC);
  while(true){
    USICR &= ~(_BV(USICS1) | ~_BV(USICS0));
    USICR |= _BV(USICLK);
    USICR &= ~_BV(USICLK);
    R = active->r;
    G = active->g;
    B = active->b;
    if(TCNT0 == 0){
      ct++;
    }
    if(ct == 50){
      i = i < 7 ? i + 1 : 0;
      active = (leds + i);
      ct = 0;
    }
    //  active = (leds + 1);
     
  }
}
