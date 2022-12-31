#include "led.h"

Adafruit_NeoPixel strip = Adafruit_NeoPixel(LED_COUNT, LED_PIN, COLORDER + LED_FREQUENCY);

void ledsetup() {
  strip.begin(); // Initialize the strip
  strip.setBrightness(LED_BRIGHTNESS); // 255 = full brightness, 127 = 50%
}

void ledcheck(bool dooropen, bool alarm, int direction) {

  if (dooropen == true){
      strip.fill(strip.Color(255,255,255)); //white
      
      //leaving fridge
      if (direction == 1){
      strip.fill(strip.Color(0, 255, 0));  // blue
    }
            
      //Entering fridge
      else if (direction == 2){
              strip.fill(strip.Color(0, 0, 255)); //green
      }

      //direction supersedes alarm
      else if (direction == 0 && alarm == true){
              strip.fill(strip.Color(255,0,0));
      }      
  }    
	else { 
        strip.fill(strip.Color(0, 0, 0)); // black
    }
  
    strip.show();
}
