#include <avr/io.h>
#include <avr/interrupt.h>
#include <inttypes.h>
#include <util/delay.h>
#include <util/atomic.h>

#define TWI_ADDRESS 0x80
#define INC 0x01
#define DEC 0x02
#define BTN_RISE 0x04
#define BTN_FALL 0x08
/*
        _____          +----+
(PCINT5/RESET/ADC0)PB5-|    |- VCC
(PCINT3/!OC1B/ADC3)PB3-| AT |-PB2(USCK/SCL/ADC1/T0/INT0/PCINT2)
 (PCINT4/OC1B/ADC2)PB4-| 85 |-PB1(MISO/DO/AIN1/OC0B/PCINT1)
                   GND-|    |-PB0(MOSI/DI/SDA/AIN0/OC0A/!OC1A/AREF/PCINT0)
                       +----+
 */

uint8_t pinb = 0xff;
int bothon = 0;
volatile int ct = 5;
uint8_t state = 0x00;

ISR(PCINT0_vect){
  uint8_t changed = PINB ^ pinb;
  pinb = PINB;
  if((changed & _BV( PB3)) && (pinb & _BV( PB3))){
    if(pinb & _BV(PB4)){
      ct++;
      state |= INC;
    }else{
      ct--;
      state |= DEC;
    }
  }
  if(changed & _BV(PB1)){
    if (pinb & _BV(PB1)){
      ct = 5;
      state |= BTN_RISE;
    }else{
      state |= BTN_FALL;
    }
  }
}


int main(void){
 
  DDRB |= _BV(PB0) | _BV(PB2);
  PORTB &= ~(_BV(PB0) | _BV(PB2));

  DDRB &= ~_BV(PB1);
  DDRB &= ~_BV(PB3);
  DDRB &= ~_BV(PB4);
  PORTB |= _BV(PB1) | _BV(PB3) | _BV(PB4); // pullup resistors

  GIMSK |= _BV(PCIE);
  PCMSK |= _BV(PCINT3) | _BV(PCINT4) | _BV(PCINT1);
  GIFR = 1 <<PCIF;

  sei();
  while(1){
    if(ct > 10)
      PORTB |= _BV(PB0);
    if(ct < 0)
      PORTB |= _BV(PB2);
    PORTB &= ~(_BV(PB0) | _BV(PB2));
    state = 0x00;
  }
}
