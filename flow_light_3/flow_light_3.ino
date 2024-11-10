#include <Adafruit_NeoPixel.h>

Adafruit_NeoPixel strip(60, 13, NEO_GRB + NEO_KHZ800);

void setup() {
  // put your setup code here, to run once:
  strip.begin();

  

}

void loop() {
  // put your main code here, to run repeatedly:
  
  int i = 0;

  for(i = 0; i < 60; i++){
    strip.setPixelColor(i, strip.Color(random(0, 50), random(0, 50), random(0, 50)));

    strip.show();
  }

  delay(1000);

}