#include <avr/interrupt.h>
#include <avr/io.h>
#include <inttypes.h>

volatile uint8_t I2C_mode;
ISR(USI_START_vect){
  
}

ISR(USI_OVF_vect){

}


void I2Cinit(){
  PORTB |= _BV(SCL);//scl high
  PORTB |= _BV(SDA);//sda high
  DDRB |= _BV(SCL);// scl output
  DDRB &= ~_BV(SDA);// sda input
  USICR |= _BV(USISIE);// enable start condition interrupt
  USICR &= ~_BV(USIOIE);//disable overflow interrupt
  USICR |= _BV(USIWM1); // enable 
  USICR &= ~_BV(USIWM0);// 2 wire mode
  USICR |= _BV(USICS1); // external positive edge clock
  USISR = 0xF0; // clear all flags and reset counter
}
