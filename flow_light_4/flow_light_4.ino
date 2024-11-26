#include <Adafruit_NeoPixel.h>

Adafruit_NeoPixel strip(60, 13, NEO_GRB + NEO_KHZ800);

void setup() {
  // put your setup code here, to run once:
  strip.begin();

  

}

void loop() {
  // put your main code here, to run repeatedly:
  
  int i = 0;

  for(i = 0; i < 30; i++){
    strip.setPixelColor(i * 2, strip.Color(50, 0, 0));
    strip.setPixelColor(i * 2 + 1, strip.Color(0, 0, 50));
  }
  strip.show();

  delay(100);

  for(i = 0; i < 60; i++){
    strip.setPixelColor(i, strip.Color(0, 0, 0));
  }
  strip.show();

  delay(100);

  for(i = 0; i < 30; i++){
    strip.setPixelColor(i * 2, strip.Color(0, 0, 50));
    strip.setPixelColor(i * 2 + 1, strip.Color(50, 0, 0));
  }
  strip.show();

  delay(100);

  for(i = 0; i < 60; i++){
    strip.setPixelColor(i, strip.Color(0, 0, 0));
  }
  strip.show();

  delay(100);

}