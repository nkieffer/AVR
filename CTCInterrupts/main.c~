#include <avr/io.h>
#include <stdbool.h>
#include <util/delay.h>
#define PRESCALER 14
int main(void){
  DDRB |= _BV(PB0) | _BV(PB4); //set PB0 & PB4 to output
  PORTB |= _BV(PB0); //turn on PB0

  TCCR0A = (1 << WGM01); //set CTC mode for timer0
  
  TCCR0B |= _BV(CS02) | _BV(CS00); //prescaler of 1024
  /*
_BV(CS00) => 1 no prescale
_BV(CS01) => 2 clk/8
_BV(CS01) | _BV(CS00) => 3 clk/64
_BV(CS02) => 4 clk/256
_BV(CS02) | _BV(CS00) => 5 clk/1024
   */
  float freq = 4; //minimum frequency obtainable by 8-bit timer
  uint16_t ct = 0;
  OCR0A = (F_CPU/(1024.0 * freq))-1;
  while(true){
    if(TIFR & (1 << OCF0A)){
      ct++;
      //  PORTB ^= _BV(PB0);//toggle led
      // PORTB ^= _BV(PB4);//toggle led
      TCCR0A = (1 << WGM01); //set CTC mode for timer0
      TIFR = (1 << OCF0A);
      TCCR0B |= _BV(CS02) | _BV(CS00);

    }

    if(ct >= 8){
      PORTB ^= _BV(PB0);//toggle led
      PORTB ^= _BV(PB4);//toggle led
      ct = 0;
    }
    
  }
}

/*
  TCCR1 |= PRESCALER;//12; //turn on timer, set prescaler to 
  TCCR1 |= _BV(CTC1);
  //TIFR = (1 << OCF1A);
   double freq = 8; //set frequency
  OCR1C =  ((1.0/ freq ) / (1.0 / ( F_CPU /(1 << (TCCR1 & 15))))) - 1;
  //OCR1A = ((float)F_CPU / ((1 << ( TCCR1 & 15)) * freq)) - 1;
  while(true){
    if(TIFR & (1 << OCF1B)){
      PORTB ^= _BV(PB0);//toggle led
      PORTB ^= _BV(PB4);//toggle led
      TIFR = (1 << OCF1B);
      TCCR1 |= PRESCALER;
      // OCR1A = 255;
      //OCR1A = ((float)F_CPU / ((1 << ( TCCR1 & 15)) * freq)) - 1;
      TCCR1 |= _BV(CTC1);
      //  OCR1A = ((1.0/ freq ) / (1.0 / ( F_CPU /(1 << (TCCR1 & 15))))) - 1;
    }
  }
}
*/
