#include <avr/io.h>
#include <test.h>
#include <util/delay.h>
void loop();
int main(){
  DDRB |= _BV(PB3);
  PORTB |= _BV(PB3);
  _delay_ms(1000);
  while(1)
    loop();
}

void loop(){
  fun();
  _delay_ms(20);
}
#warning Done
