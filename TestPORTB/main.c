#include <avr/io.h>
#include <util/delay.h>
/*
        _____          +----+
(PCINT5/RESET/ADC0)PB5-|    |- VCC
(PCINT3/!OC1B/ADC3)PB3-| AT |-PB2(USCK/SCL/ADC1/T0/INT0/PCINT2)
 (PCINT4/OC1B/ADC2)PB4-| 85 |-PB1(MISO/DO/AIN1/OC0B/PCINT1)
                   GND-|    |-PB0(MOSI/DI/SDA/AIN0/OC0A/!OC1A/AREF/PCINT0)
                       +----+
 */
int main(void){
  DDRB |= _BV(PB0) | _BV(PB2);
  PORTB = _BV(PB0) | _BV(PB2);;
  while(1){
    PORTB ^= (_BV(PB0) | _BV(PB2));
    _delay_ms(500);
  }
 }
