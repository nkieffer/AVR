#include <avr/io.h>
#include <avr/interrupt.h>
#include <inttypes.h>
#include <util/delay.h>
#include <util/atomic.h>
#include "I2C.h"
#define TWI_ADDRESS 0x01

/*
        _____          +----+
(PCINT5/RESET/ADC0)PB5-|    |- VCC
(PCINT3/!OC1B/ADC3)PB3-| AT |-PB2(USCK/SCL/ADC1/T0/INT0/PCINT2)
 (PCINT4/OC1B/ADC2)PB4-| 85 |-PB1(MISO/DO/AIN1/OC0B/PCINT1)
                   GND-|    |-PB0(MOSI/DI/SDA/AIN0/OC0A/!OC1A/AREF/PCINT0)
                       +----+
 */
extern uint8_t I2C_mode = I2C_STATE_IDLE;
extern volatile uint8_t dataAvailable;
int main(void){
  DDRB |= _BV(PB1) | _BV(PB4);
  I2Cinit(TWI_ADDRESS);
  sei();
  uint8_t da;
  while(1){
    cli();
    da = dataAvailable;
    dataAvailable = 0;
    sei();
    if(da == 1){
      PORTB |= _BV(PB1);
      _delay_ms(100);
      PORTB &= ~_BV(PB1);
    }



  }
  
}
