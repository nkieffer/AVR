#include <inttypes.h>
#include "rgbled.h"

RGBLed rgbled(uint8_t r, uint8_t g, uint8_t b, uint8_t id){
  RGBLed led;
  led.r = r;
  led.g = g;
  led.b = b;
  led.id = id;
  return led;
}

void dim(RGBLed * led){
  led->r = led->r > 0 ? led->r - 5 : led->r;
  led->g = led->g > 0 ? led->g - 5 : led->g;
  led->b = led->b > 0 ? led->b - 5 : led->b;
}

void bright(RGBLed * led){
  led->r = led->r < 255 ? led->r + 5 : led->r;
  led->g = led->g < 255 ? led->g + 5 : led->g;
  led->b = led->b < 255 ? led->b + 5 : led->b;
}
