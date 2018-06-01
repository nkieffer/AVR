#include <avr/io.h>
#include <stdbool.h>
#include <util/delay.h>
#define LIMIT 5
int main(void){
  DDRB |= _BV(PB0) | _BV(PB4); //set PB0 & PB4 to output
  PORTB |= _BV(PB0); //turn on PB0
  TCCR1 |= 14; //turn on timer, set prescaler to 
  double freq = 1; //set frequency
  uint8_t seconds = 0;
  while(true){
    // (F_CPU / (1 << (TCCR1 & 15)) * freq) - 1
    if(TCNT1 >= ((1.0 / freq ) / (1.0 / ( F_CPU /(1 << (TCCR1 & 15))))) - 1){
      seconds++;
      if(seconds > LIMIT){
	PORTB ^= _BV(PB0);//toggle led
	PORTB ^= _BV(PB4);//toggle led
	seconds = 0;
      }
      TCNT1 = 0; //reset timer counter
      TCCR1 = 14; //reset prescaler and start timer aain
    }
  }
}
