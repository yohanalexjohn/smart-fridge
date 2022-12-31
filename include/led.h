#ifndef LED_H
#define LED_H

#include <Arduino.h>
#include <Adafruit_NeoPixel.h> 

#define LED_COUNT       12     
#define LED_PIN         25        
#define LED_TYPE        WS2811
#define COLORDER        NEO_GRB
#define LED_FREQUENCY   NEO_KHZ800
#define LED_BRIGHTNESS  50

void ledsetup();
void ledcheck(bool dooropen, bool alarm, int direction);

#endif
