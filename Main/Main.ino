#include <Adafruit_NeoPixel.h>

#define NUM 60

Adafruit_NeoPixel strip(NUM, 13, NEO_GRB + NEO_KHZ800);

void setup() {
  // put your setup code here, to run once:
  strip.begin();

  int i = 0;

  for(i = 0; i < NUM; i++){
    strip.setPixelColor(i, strip.Color(50, 50, 50));
  }

  strip.show();

}

void loop() {
  // put your main code here, to run repeatedly:
  
  

}