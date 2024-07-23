#ifndef LED_ARRAY_H
#define LED_ARRAY_H

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

class LED_Array {
  private:
    int ledPin;
    int mapping[8];
    String display = "XXXXXXXX";
    Adafruit_NeoPixel pixels;

  public:
    LED_Array(int pin, const int* mapping);
    void setBrightness(int brightness);
    void mirror(String face);
    void setColor(int r, int g, int b);
    String getString();
};

#endif