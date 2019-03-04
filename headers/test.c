#include <test.h>
#include <avr/io.h>
int fun(){
  PORTB ^= _BV(PB3);
  return 1;
}
