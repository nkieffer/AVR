#include <avr/io.h>
#include <power.h>
#include <util/delay.h>
void setup(void){
  check_power_down();
  DDRB |= _BV(PB3);
}

void loop(void){
  PORTB ^= _BV(PB3);
  _delay_ms(20);
}

int main  (void){
  setup();
  while(1) loop();
}
