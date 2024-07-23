// Cube_Lights.h
#ifndef CUBE_LIGHTS_H
#define CUBE_LIGHTS_H

#include <Arduino.h>
#include "LED_Array.h"

class Cube_Lights {
  private:
    LED_Array& up;
    LED_Array& down;
    LED_Array& right;
    LED_Array& left;
    LED_Array& back;
    String cube_string;

  public:
    Cube_Lights(LED_Array& UP, LED_Array& DOWN, LED_Array& RIGHT, LED_Array& LEFT, LED_Array& BACK);
    void setBrightness(int brightness);
    void setColor(int r, int g, int b);
    void setCubeString(String Cube_String);
    void resetCubeString();
    void setMirror();
    void rotate(String move);

    void rotateU();
    void rotateUPrime();
    void rotateU2();

    void rotateD();
    void rotateDPrime();
    void rotateD2();

    void rotateR();
    void rotateRPrime();
    void rotateR2();

    void rotateL();
    void rotateLPrime();
    void rotateL2();

    void rotateF();
    void rotateFPrime();
    void rotateF2();

    void rotateB();
    void rotateBPrime();
    void rotateB2();   

};

#endif