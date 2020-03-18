#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/sfr_defs.h>
#include <stdlib.h>
#define LED(idx, DDRB, PORTB) leds[(idx)].ddrb = (DDRB);leds[(idx)].portb=(PORTB); 

volatile uint16_t analog;
ISR(ADC_vect){
  analog = ((ADCH << 8) | ADCL);
 }

typedef struct LED{
  uint8_t ddrb;
  uint8_t portb;
} LED;

void turnOn(LED led){
  PORTB = led.portb;
  DDRB = led.ddrb;
  DDRB &= ~_BV(PB4);
}

void lightPattern( uint16_t p, LED * leds){
  int i;
  for(i = 0; i < 12; i++){
    if((p & (1 << i)) >> i == 1){
      turnOn(leds[i]);
      _delay_ms(1);
    }
  }
}
/*
        _____          +---+
(PCINT5/RESET/ADC0)PB5-|   |- VCC
(PCINT3/!OC1B/ADC3)PB3-|   |-PB2(USCK/SCL/ADC1/T0/INT0/PCINT2)
 (PCINT4/OC1B/ADC2)PB4-|   |-PB1(MISO/DO/AIN1/OC0B/PCINT1)
                   GND-|   |-PB0(MOSI/DI/SDA/AIN0/OC0A/!OC1A/AREF/PCINT0)
                       +---+
 */
int led = 0;
uint32_t ct = 0;
uint16_t pat;

int main(void){
  LED leds[12];
  ADCSRA |= _BV(ADEN);//turn on ADC single conversion mode
  ADMUX |= _BV(MUX1);//ADC2
  DIDR0 |= _BV(ADC2D);//turn of digital ADC
  sei();

  //  idx, DDRB, PORTB
  LED(0, 0xf3, 0x01); //0x0001;
  LED(1, 0xf6, 0x02); //0x0002;
  LED(2, 0xfc, 0x04); //0x0004;
  LED(3, 0xf9, 0x08); //0x0008;
  LED(4, 0xf5, 0x01); //0x0010;
  LED(5, 0xfa, 0x02); //0x0020;
  LED(6, 0xf5, 0x04); //0x0040;
  LED(7, 0xfa, 0x08); //0x0080;
  LED(8, 0xf9, 0x01); //0x0100;
  LED(9, 0xf3, 0x02); //0x0200;
  LED(10, 0xf6, 0x04); //0x0400;
  LED(11, 0xfc, 0x08); //0x0800;

  while(1){
    uint16_t lvl;
    ADCSRA |= _BV(ADSC); //start the ADC
    loop_until_bit_is_clear(ADCSRA, ADSC);//wait until it finishes.
    lvl = (uint16_t)((ADC / 1023.0) * 12);
    pat = 0;
    while(lvl--)
      pat |= (1 << lvl);
    lightPattern(pat, leds);
  }
}
