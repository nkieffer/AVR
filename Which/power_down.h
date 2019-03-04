#ifndef POWER_DOWN_H_
#define POWER_DOWN_H_
extern int Power __attribute__((section (".noinit")));
void power_down();
void check_power_down();

#endif
