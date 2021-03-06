#include <avr/sleep.h>
#include <avr/io.h>
#include "power_down.h"
int Power __attribute__((section (".noinit")));

void power_down(){
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  ADCSRA &= ~_BV(ADEN);
  sleep_enable();
  sleep_cpu();

}

void check_power_down(){
  Power = !Power;
  if(!Power) power_down();
}
