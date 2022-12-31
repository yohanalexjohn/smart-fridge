#ifndef LED_H
#define LED_H

#include <Arduino.h>
#include <Adafruit_NeoPixel.h> 


#define LED_COUNT       12     // Number of LEDs in the strip
#define LED_PIN         25         // esp32 data pin
#define LED_TYPE        WS2811
#define COLORDER		NEO_GRB
//#define COLORDER      GRB
#define LED_FREQUENCY   NEO_KHZ800

#define maxPSU 450 // 450mW is suitable to stay under 5V
#define brightCheck 16 // 26 //96 // for setBrightness(16)

// Adafruit_NeoPixel strip = Adafruit_NeoPixel(LED_COUNT, LED_PIN, COLORDER + LED_FREQUENCY);


void ledsetup();
void ledcheck(bool dooropen, bool alarm, int direction);

#endif