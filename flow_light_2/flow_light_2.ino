#include <Adafruit_NeoPixel.h>

Adafruit_NeoPixel strip(60, 13, NEO_GRB + NEO_KHZ800);

void setup() {
  // put your setup code here, to run once:
  strip.begin();

  

}

void loop() {
  // put your main code here, to run repeatedly:
  
  int i = 0;

  for(i = 0; i < 63; i++){
    strip.setPixelColor(i - 2, strip.Color(0, 0, 0));
    strip.setPixelColor(i - 1, strip.Color(200, 255, 0));
    strip.setPixelColor(i, strip.Color(0, 0, 255));

    strip.show();
    delay(500);
  }

  

}