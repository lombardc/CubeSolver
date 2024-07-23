#include "LED_Array.h"
#include <Adafruit_NeoPixel.h>

LED_Array::LED_Array(int pin, const int* mapping) : ledPin(pin), pixels(48, pin, NEO_GRB + NEO_KHZ800) {
    for (int i = 0; i < 8; i++) {
        this->mapping[i] = mapping[i];
    }
    pixels.begin();
}

void LED_Array::setBrightness(int brightness){
  pixels.setBrightness(brightness);
}

void LED_Array::mirror(String face){
  this->display[0] = face[mapping[0]];
  this->display[1] = face[mapping[1]];
  this->display[2] = face[mapping[2]];
  this->display[3] = face[mapping[3]];
  this->display[4] = face[mapping[4]];
  this->display[5] = face[mapping[5]];
  this->display[6] = face[mapping[6]];
  this->display[7] = face[mapping[7]];

  for (int face = 0; face < 8; face++) {
      int r, g, b;
      switch (display[face]) {
          case 'U': r = 0;   g = 0;   b = 255; break;
          case 'F': r = 255; g = 255; b = 255; break;
          case 'B': r = 255; g = 255; b = 0;   break;
          case 'L': r = 255; g = 100; b = 0;   break;
          case 'R': r = 255; g = 0;   b = 0;   break;
          case 'D': r = 0;   g = 255; b = 0;   break;
          default:  r = 0;   g = 0;   b = 0;   break; // Handle unexpected characters
      }

      for (int j = 0; j < 6; j++) {
          int i = face * 6 + j;
          if (i < 48) {
              pixels.setPixelColor(i, r, g, b);
          }
      }
  }
  pixels.show();
}

void LED_Array::setColor(int r, int g, int b){
  for(int i=0; i<48; i++) {
    pixels.setPixelColor(i, r, g, b);
  }
  pixels.show();
}

String LED_Array::getString(){
  return this->display;
}