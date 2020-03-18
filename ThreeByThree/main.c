#include <avr/interrupt.h>
#include <util/delay.h>
#define DELAY 1
typedef struct LED{
  uint8_t ddrb;
  uint8_t portb;
} LED;

void turnOn(LED led){
  DDRB = led.ddrb;
  PORTB = led.portb;
}

void lightPattern(uint8_t p, LED * leds){
  int i;
  for(i = 0; i < 6; i++){
    if((p & (1 << i)) >> i == 1){
      turnOn(leds[i]);
    }
  }
}

int main(void){
  LED leds[7];
  // uint8_t * pattern;
  /* uint8_t patterns[] = {0b00000001, 0b00000010, 0b00000100, 0b00001000,
			0b00010000, 0b00100000, 0b00010000, 0b00001000,
			0b00000100, 0b00000010, 0b00000001};
  */
// pattern = patterns;
  //uint16_t ct = 0;
  leds[0].ddrb = 0xfd;
  leds[0].portb = 0x04;
  
  leds[1].ddrb = 0xfe;
  leds[1].portb = 0x04;
  
  leds[2].ddrb = 0xfb;
  leds[2].portb = 0x06; //0x02
  
  leds[3].ddrb = 0xfd;
  leds[3].portb = 0x03;
  
  leds[4].ddrb = 0xfe;
  leds[4].portb = 0x02;
  
  leds[5].ddrb = 0xfb;
  leds[5].portb = 0x01;
  
  leds[6].ddrb = 0xf4;
  leds[6].portb = 0x04;
  while(1){
    turnOn(leds[5]);
    /* lightPattern(*pattern, leds); */
    /* if(ct >= 0x0900){ */
    /*   pattern = pattern <= patterns + 8 ? pattern + 1 : patterns; */
    /* } */
    
    /* ct = ct >=  0x0900 ? 0 : ct + 13; */
  }
}
