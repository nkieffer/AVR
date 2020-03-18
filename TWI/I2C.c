#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>
#include <inttypes.h>
#include "I2C.h"
volatile uint8_t I2C_mode;
volatile uint8_t dataAvailable;
volatile uint8_t buffer = 0;
uint8_t I2C_addr;
ISR(USI_START_vect){
  //clear start condition flag, reset counter
  uint8_t tmpUSISR = USISR;
  tmpUSISR &= ~(_BV(USISIF) | _BV(USICNT3) | _BV(USICNT2) | _BV(USICNT1) | _BV(USICNT0));
  DDRB &= ~_BV(SDA);
  I2C_mode = I2C_STATE_CHECK_ADDR;
  while((PINB * (_BV(SCL)) & !(tmpUSISR & (1<<USIPF))));
  USISR = 0xF0 | (0x0<<USICNT0) ;
	
  //  USICR &= ~_BV(USISIE); //disable start condition interrupt
  USICR |= _BV(USIOIE); //enable overflow interrupt	     

  //dataAvailable = 1;
}

ISR(USI_OVF_vect){
  uint8_t addr;
  uint8_t write;
  switch(I2C_mode){
  case I2C_STATE_CHECK_ADDR:
    addr = USIBR >> 1;
    write = USIBR & 0x01;
    if(addr == I2C_addr){
      I2C_mode = write ? I2C_STATE_WRITE_DATA : I2C_STATE_READ_DATA;
    }
    USISR = 0x7|(0x0e<<USICNT0);
    break;
  case I2C_STATE_CHECK_REPLY:
    if(USIBR){
      I2Cinit(I2C_addr);
      return;
    }
  case I2C_STATE_WRITE_DATA:
    I2C_mode = I2C_STATE_WRITE_ACK;
    USIDR = 0x55;
    DDRB |= _BV(SDA);
    USISR |= 0x70 | (0x0 << USICNT0);
    break;
  case I2C_STATE_WRITE_ACK:
    dataAvailable = 1;
    I2C_mode = I2C_STATE_CHECK_REPLY;
    DDRB &= ~_BV(SDA);
    USIDR = 0;
    USISR |= 0x70 | (0x0e << USICNT0);
    break;
  }
}

void I2Cinit(uint8_t thisAddr){
  I2C_mode = I2C_STATE_IDLE;
  dataAvailable = 0;
  I2C_addr = thisAddr;
  PORTB |= _BV(SCL);//scl high
  PORTB |= _BV(SDA);//sda high
  DDRB |= _BV(SCL);// scl input
  DDRB &= ~_BV(SDA);// sda input
  USICR = (1<<USISIE)|(0<<USIOIE)| // Enable Start Condition. Disable Overflow.
    (1<<USIWM1)|(0<<USIWM0)|       // Set USI in Two-wire mode. No USI Counter overflow prior to first Start Condition (potentail failure)
    (1<<USICS1)|(0<<USICS0)|(0<<USICLK)| // Shift Register Clock Source = External, positive edge
    (0<<USITC);
  USISR = 0x70; // clear all flags and reset counter
}
