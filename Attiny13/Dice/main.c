#include <inttypes.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <power.h>
uint8_t led;
volatile uint8_t number = 0;
volatile uint8_t stop = 0;
uint8_t pressed = 0;

ISR(INT0_vect){
  pressed = 1;
  stop = !stop;
  /*  PORTB = PORTB & _BV(PB3) ?
    PORTB & ~_BV(PB3) : 
    PORTB | _BV(PB3);*/
}
void toggleLed(uint8_t number){
  DDRB |= _BV(PB3);
  PORTB &= _BV(PB3);  
  cli();
  switch(number){
  case 0:
    DDRB |= _BV(PB2) | _BV(PB0);
    DDRB &= ~_BV(PB4);
    PORTB |= _BV(PB2);
    break;
  case 1:
    DDRB |= _BV(PB2) | _BV(PB4);
    DDRB &= ~_BV(PB0);
    PORTB |= _BV(PB2);
    break;
  case 2:
    DDRB |= _BV(PB0) | _BV(PB4);
    DDRB &= ~_BV(PB2);
    PORTB |= _BV(PB0);
    break;
  case 3:
    DDRB |= _BV(PB0) | _BV(PB2);
    DDRB &= ~_BV(PB4);
    PORTB |= _BV(PB0);
    break;
  case 4: 
    DDRB |= _BV(PB4) | _BV(PB2);
    DDRB &= ~_BV(PB0);
    PORTB |= _BV(PB4);
    break;
  case 5:
    DDRB |= _BV(PB4) | _BV(PB0);
    DDRB &= ~_BV(PB2);
    PORTB |= _BV(PB4);
    break;
  }
  sei();
}

uint8_t lfsr(uint8_t seed){
  uint8_t a = (seed & (1 << 3)) >> 3;
  uint8_t b = (seed & (1 << 6)) >> 6;
  uint8_t c = (seed & (1 << 2)) >> 2;
  uint8_t d = (a ^ b ^ c);
  seed = (seed >> 1) | (d << 7);
  return seed;
}

void setup(void){
  check_power_down();
  DDRB &= ~_BV(PB1); //debounced with external pullup resistor
  DDRB |= _BV(PB3);
  GIMSK |= _BV(INT0);
  MCUCR |= _BV(ISC01);
  // MCUCR |= _BV(ISC00) | _BV(ISC01); //rising edge
  sei();
}

void loop(void){
  cli();
  if(pressed){
    //cli();
    _delay_ms(10);
    //sei();
    pressed = 0;
  }
  sei();
  if(!stop){
    PORTB = 0;
    number = (number + 1) % 6;
    toggleLed(number);
    _delay_ms(2);
    //stop = 1;
  }else{
    PORTB = _BV(PB3);
    led = 0;
    while(led <= number){
      toggleLed(led);
      led++;
    }
  }

  
}

int main(void){
  setup();
  while(1) loop();
}
