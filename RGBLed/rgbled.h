#include <inttypes.h>
#ifndef RGBLED_H
#define RGBLED_H
typedef struct RGBLed {
  uint8_t r;
  uint8_t g;
  uint8_t b;
  uint8_t id;
} RGBLed;

RGBLed rgbled(uint8_t r, uint8_t g , uint8_t b, uint8_t id);
void dim(RGBLed *);
void bright(RGBLed *); 
#endif
