#include <avr/io.h>
#include <avr/sleep.h>
#include <power.h>
int power __attribute__((section (".noinit")));
void power_down(){
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  ADCSRA &= ~_BV(ADEN);
  sleep_enable();
  sleep_cpu();
}

void check_power_down(){
  power = !power;
  if(!power) power_down();
}
