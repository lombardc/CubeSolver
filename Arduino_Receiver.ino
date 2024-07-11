// SOLV R2-U2-L'-F-U2-B-R'-U2-F-D-F'-L-B2-U-F2-U-L2-F2-U'-R'-B'-D'-U-L-D
// SOLV D'-L'-U'-D-B-R-U-F2-L2-U'-F2-U'-B2-L'-F-D'-F'-U2-R-B'-U2-F'-L-U2-R2
// MIRR UUUUUUUUURRRRRRRRRFFFFFFFFFDDDDDDDDDLLLLLLLLLBBBBBBBBB
#include <AccelStepper.h>
#include <Adafruit_NeoPixel.h>
#include <StringSplitter.h>

#define LED_PIN_rouge 29
#define LED_PIN_bleu 28
#define LED_PIN_orange 30
#define LED_PIN_vert 31
#define LED_PIN_jaune 40

#define LED_COUNT 48
#define STEPS 800

AccelStepper blanc(AccelStepper::DRIVER, 2, 52);
AccelStepper orange(AccelStepper::DRIVER, 3, 50);
AccelStepper jaune(AccelStepper::DRIVER, 4, 48);
AccelStepper vert(AccelStepper::DRIVER, 5, 46);
AccelStepper bleu(AccelStepper::DRIVER, 6, 44);
AccelStepper rouge(AccelStepper::DRIVER, 7, 42);

Adafruit_NeoPixel strip_vert(LED_COUNT, LED_PIN_vert, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip_jaune(LED_COUNT, LED_PIN_jaune, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip_rouge(LED_COUNT, LED_PIN_rouge, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip_bleu(LED_COUNT, LED_PIN_bleu, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip_orange(LED_COUNT, LED_PIN_orange, NEO_GRB + NEO_KHZ800);

float MOTOR_SPEED = 4000.0; //4000 // good lub, 5500
float MOTOR_ACC = 200000;//200000.0;
String OP_CODE;


String leds_u = "XXXXXXXX";
String leds_d = "XXXXXXXX";
String leds_r = "XXXXXXXX";
String leds_l = "XXXXXXXX";
String leds_f = "XXXXXXXX";
String leds_b = "XXXXXXXX";

String cube_string = "UUUUUUUUURRRRRRRRRFFFFFFFFFDDDDDDDDDLLLLLLLLLBBBBBBBBB";

void setup()
{
    rouge.setMaxSpeed(MOTOR_SPEED);
    rouge.setAcceleration(MOTOR_ACC);
    rouge.setEnablePin(22);
    rouge.setPinsInverted(false, false, true);
    rouge.disableOutputs();
    rouge.setCurrentPosition(0);

    blanc.setMaxSpeed(MOTOR_SPEED);
    blanc.setAcceleration(MOTOR_ACC);
    blanc.setEnablePin(27);
    blanc.setPinsInverted(false, false, true);
    blanc.disableOutputs();
    blanc.setCurrentPosition(0);

    orange.setMaxSpeed(MOTOR_SPEED);
    orange.setAcceleration(MOTOR_ACC);
    orange.setEnablePin(26);
    orange.setPinsInverted(false, false, true);
    orange.disableOutputs();
    orange.setCurrentPosition(0);

    jaune.setMaxSpeed(MOTOR_SPEED);
    jaune.setAcceleration(MOTOR_ACC);
    jaune.setEnablePin(25);
    jaune.setPinsInverted(false, false, true);
    jaune.disableOutputs();
    jaune.setCurrentPosition(0);

    vert.setMaxSpeed(MOTOR_SPEED);
    vert.setAcceleration(MOTOR_ACC);
    vert.setEnablePin(24);
    vert.setPinsInverted(false, false, true);
    vert.disableOutputs();
    vert.setCurrentPosition(0);

    bleu.setMaxSpeed(MOTOR_SPEED);
    bleu.setAcceleration(MOTOR_ACC);
    bleu.setEnablePin(23);
    bleu.setPinsInverted(false, false, true);
    bleu.disableOutputs();
    bleu.setCurrentPosition(0);

    strip_vert.begin();
    strip_vert.setBrightness(50);
    strip_jaune.begin();
    strip_jaune.setBrightness(50);
    strip_orange.begin();
    strip_orange.setBrightness(50);
    strip_rouge.begin();
    strip_rouge.setBrightness(50);
    strip_bleu.begin();
    strip_bleu.setBrightness(50);
    strip_vert.show();
    strip_bleu.show();
    strip_rouge.show();
    strip_orange.show();
    strip_jaune.show();
    Serial3.begin(115200);
    lights("SOLV");
}


void leds_power(String OPCODE) {
    strip_vert.setBrightness(OPCODE.toInt());
    strip_jaune.setBrightness(OPCODE.toInt());
    strip_orange.setBrightness(OPCODE.toInt());
    strip_rouge.setBrightness(OPCODE.toInt());
    strip_bleu.setBrightness(OPCODE.toInt());
    strip_vert.show();
    strip_bleu.show();
    strip_rouge.show();
    strip_orange.show();
    strip_jaune.show();
}
// Define a type alias for rotation functions
using RotateFunction = void (*)(String&);

// Lookup table for rotation functions
struct RotationMapping {
  const char* command;
  RotateFunction function;
};


void rotateU(String &cube_string) {
  String temp = cube_string;
  cube_string[18] = temp[9];
  cube_string[19] = temp[10];
  cube_string[20] = temp[11];

  cube_string[36] = temp[18];
  cube_string[37] = temp[19];
  cube_string[38] = temp[20];

  cube_string[45] = temp[36];
  cube_string[46] = temp[37];
  cube_string[47] = temp[38];

  cube_string[9] = temp[45];
  cube_string[10] = temp[46];
  cube_string[11] = temp[47];

  cube_string[0] = temp[6];
  cube_string[1] = temp[3];
  cube_string[2] = temp[0];
  cube_string[3] = temp[7];
  cube_string[5] = temp[1];
  cube_string[6] = temp[8];
  cube_string[7] = temp[5];
  cube_string[8] = temp[2];
  mirror_u(cube_string.substring(0, 9));
  mirror_r(cube_string.substring(9, 18));
  mirror_f(cube_string.substring(18, 27));
  mirror_l(cube_string.substring(36, 45));
  mirror_b(cube_string.substring(45));
  show_led_strip(strip_jaune, leds_b);
  show_led_strip(strip_orange, leds_l);
  show_led_strip(strip_bleu, leds_u);
  show_led_strip(strip_rouge, leds_r);
}
void rotateUPrime(String &cube_string) {
  String temp = cube_string;
  cube_string[18] = temp[36];
  cube_string[19] = temp[37];
  cube_string[20] = temp[38];

  cube_string[36] = temp[45];
  cube_string[37] = temp[46];
  cube_string[38] = temp[47];

  cube_string[45] = temp[9];
  cube_string[46] = temp[10];
  cube_string[47] = temp[11];

  cube_string[9] = temp[18];
  cube_string[10] = temp[19];
  cube_string[11] = temp[20];

  cube_string[0] = temp[2];
  cube_string[1] = temp[5];
  cube_string[2] = temp[8];
  cube_string[3] = temp[1];
  cube_string[5] = temp[7];
  cube_string[6] = temp[0];
  cube_string[7] = temp[3];
  cube_string[8] = temp[6];
  mirror_u(cube_string.substring(0, 9));
  mirror_r(cube_string.substring(9, 18));
  mirror_f(cube_string.substring(18, 27));
  mirror_l(cube_string.substring(36, 45));
  mirror_b(cube_string.substring(45));
  show_led_strip(strip_jaune, leds_b);
  show_led_strip(strip_orange, leds_l);
  show_led_strip(strip_bleu, leds_u);
  show_led_strip(strip_rouge, leds_r);
}
void rotateU2(String &cube_string) {
  String temp = cube_string;
  cube_string[18] = temp[45];
  cube_string[19] = temp[46];
  cube_string[20] = temp[47];

  cube_string[36] = temp[9];
  cube_string[37] = temp[10];
  cube_string[38] = temp[11];

  cube_string[45] = temp[18];
  cube_string[46] = temp[19];
  cube_string[47] = temp[20];

  cube_string[9] = temp[36];
  cube_string[10] = temp[37];
  cube_string[11] = temp[38];

  cube_string[8] = temp[0];
  cube_string[7] = temp[1];
  cube_string[6] = temp[2];
  cube_string[5] = temp[3];
  cube_string[3] = temp[5];
  cube_string[2] = temp[6];
  cube_string[1] = temp[7];
  cube_string[0] = temp[8];
  mirror_u(cube_string.substring(0, 9));
  mirror_r(cube_string.substring(9, 18));
  mirror_f(cube_string.substring(18, 27));
  mirror_l(cube_string.substring(36, 45));
  mirror_b(cube_string.substring(45));
  show_led_strip(strip_jaune, leds_b);
  show_led_strip(strip_orange, leds_l);
  show_led_strip(strip_bleu, leds_u);
  show_led_strip(strip_rouge, leds_r);
}
void rotateD(String &cube_string) {
  String temp = cube_string;
  cube_string[24] = temp[42];
  cube_string[25] = temp[43];
  cube_string[26] = temp[44];

  cube_string[42] = temp[51];
  cube_string[43] = temp[52];
  cube_string[44] = temp[53];

  cube_string[51] = temp[15];
  cube_string[52] = temp[16];
  cube_string[53] = temp[17];

  cube_string[15] = temp[24];
  cube_string[16] = temp[25];
  cube_string[17] = temp[26];

  cube_string[27] = temp[33];
  cube_string[28] = temp[30];
  cube_string[29] = temp[27];
  cube_string[30] = temp[34];
  cube_string[32] = temp[28];
  cube_string[33] = temp[35];
  cube_string[34] = temp[32];
  cube_string[35] = temp[29];
  mirror_r(cube_string.substring(9, 18));
  mirror_f(cube_string.substring(18, 27));
  mirror_d(cube_string.substring(27, 36));
  mirror_l(cube_string.substring(36, 45));
  mirror_b(cube_string.substring(45));
  show_led_strip(strip_jaune, leds_b);
  show_led_strip(strip_orange, leds_l);
  show_led_strip(strip_vert, leds_d);
  show_led_strip(strip_rouge, leds_r);
}
void rotateD2(String &cube_string) {
  String temp = cube_string;
  cube_string[24] = temp[51];
  cube_string[25] = temp[52];
  cube_string[26] = temp[53];

  cube_string[42] = temp[15];
  cube_string[43] = temp[16];
  cube_string[44] = temp[17];

  cube_string[51] = temp[24];
  cube_string[52] = temp[25];
  cube_string[53] = temp[26];

  cube_string[15] = temp[42];
  cube_string[16] = temp[43];
  cube_string[17] = temp[44];

  cube_string[27] = temp[35];
  cube_string[28] = temp[34];
  cube_string[29] = temp[33];
  cube_string[30] = temp[32];
  cube_string[32] = temp[30];
  cube_string[33] = temp[29];
  cube_string[34] = temp[28];
  cube_string[35] = temp[27];
  mirror_r(cube_string.substring(9, 18));
  mirror_f(cube_string.substring(18, 27));
  mirror_d(cube_string.substring(27, 36));
  mirror_l(cube_string.substring(36, 45));
  mirror_b(cube_string.substring(45));
  show_led_strip(strip_jaune, leds_b);
  show_led_strip(strip_orange, leds_l);
  show_led_strip(strip_vert, leds_d);
  show_led_strip(strip_rouge, leds_r);
}
void rotateDPrime(String &cube_string) {
  String temp = cube_string;
  cube_string[24] = temp[15];
  cube_string[25] = temp[16];
  cube_string[26] = temp[17];

  cube_string[42] = temp[24];
  cube_string[43] = temp[25];
  cube_string[44] = temp[26];

  cube_string[51] = temp[42];
  cube_string[52] = temp[43];
  cube_string[53] = temp[44];

  cube_string[15] = temp[51];
  cube_string[16] = temp[52];
  cube_string[17] = temp[53];

  cube_string[27] = temp[29];
  cube_string[28] = temp[32];
  cube_string[29] = temp[35];
  cube_string[30] = temp[28];
  cube_string[32] = temp[34];
  cube_string[33] = temp[27];
  cube_string[34] = temp[30];
  cube_string[35] = temp[33];
  mirror_r(cube_string.substring(9, 18));
  mirror_f(cube_string.substring(18, 27));
  mirror_d(cube_string.substring(27, 36));
  mirror_l(cube_string.substring(36, 45));
  mirror_b(cube_string.substring(45));
  show_led_strip(strip_jaune, leds_b);
  show_led_strip(strip_orange, leds_l);
  show_led_strip(strip_vert, leds_d);
  show_led_strip(strip_rouge, leds_r);
}
void rotateF(String &cube_string) {
  String temp = cube_string;
  cube_string[6] = temp[44];
  cube_string[7] = temp[41];
  cube_string[8] = temp[38];

  cube_string[44] = temp[29];
  cube_string[41] = temp[28];
  cube_string[38] = temp[27];

  cube_string[29] = temp[9];
  cube_string[28] = temp[12];
  cube_string[27] = temp[15];

  cube_string[9] = temp[6];
  cube_string[12] = temp[7];
  cube_string[15] = temp[8];

  cube_string[18] = temp[24];
  cube_string[19] = temp[21];
  cube_string[20] = temp[18];
  cube_string[21] = temp[25];
  cube_string[23] = temp[19];
  cube_string[24] = temp[26];
  cube_string[25] = temp[23];
  cube_string[26] = temp[20];
  mirror_u(cube_string.substring(0, 9));
  mirror_r(cube_string.substring(9, 18));
  mirror_f(cube_string.substring(18, 27));
  mirror_d(cube_string.substring(27, 36));
  mirror_l(cube_string.substring(36, 45));
  show_led_strip(strip_orange, leds_l);
  show_led_strip(strip_vert, leds_d);
  show_led_strip(strip_bleu, leds_u);
  show_led_strip(strip_rouge, leds_r);
}
void rotateFPrime(String &cube_string) {
  String temp = cube_string;
  cube_string[6] = temp[9];
  cube_string[7] = temp[12];
  cube_string[8] = temp[15];

  cube_string[44] = temp[6];
  cube_string[41] = temp[7];
  cube_string[38] = temp[8];

  cube_string[29] = temp[44];
  cube_string[28] = temp[41];
  cube_string[27] = temp[38];

  cube_string[9] = temp[29];
  cube_string[12] = temp[28];
  cube_string[15] = temp[27];

  cube_string[18] = temp[20];
  cube_string[19] = temp[23];
  cube_string[20] = temp[26];
  cube_string[21] = temp[19];
  cube_string[23] = temp[25];
  cube_string[24] = temp[18];
  cube_string[25] = temp[21];
  cube_string[26] = temp[24];
  mirror_u(cube_string.substring(0, 9));
  mirror_r(cube_string.substring(9, 18));
  mirror_f(cube_string.substring(18, 27));
  mirror_d(cube_string.substring(27, 36));
  mirror_l(cube_string.substring(36, 45));
  show_led_strip(strip_orange, leds_l);
  show_led_strip(strip_vert, leds_d);
  show_led_strip(strip_bleu, leds_u);
  show_led_strip(strip_rouge, leds_r);
}
void rotateF2(String &cube_string) {
  String temp = cube_string;
  cube_string[6] = temp[29];
  cube_string[7] = temp[28];
  cube_string[8] = temp[27];

  cube_string[44] = temp[9];
  cube_string[41] = temp[12];
  cube_string[38] = temp[15];

  cube_string[29] = temp[6];
  cube_string[28] = temp[7];
  cube_string[27] = temp[8];

  cube_string[9] = temp[44];
  cube_string[12] = temp[41];
  cube_string[15] = temp[38];

  cube_string[18] = temp[26];
  cube_string[19] = temp[25];
  cube_string[20] = temp[24];
  cube_string[21] = temp[23];
  cube_string[23] = temp[21];
  cube_string[24] = temp[20];
  cube_string[25] = temp[19];
  cube_string[26] = temp[18];
  mirror_u(cube_string.substring(0, 9));
  mirror_r(cube_string.substring(9, 18));
  mirror_f(cube_string.substring(18, 27));
  mirror_d(cube_string.substring(27, 36));
  mirror_l(cube_string.substring(36, 45));
  show_led_strip(strip_orange, leds_l);
  show_led_strip(strip_vert, leds_d);
  show_led_strip(strip_bleu, leds_u);
  show_led_strip(strip_rouge, leds_r);
}
void rotateB(String &cube_string) {
  String temp = cube_string;
  cube_string[0] = temp[11];
  cube_string[1] = temp[14];
  cube_string[2] = temp[17];

  cube_string[11] = temp[35];
  cube_string[14] = temp[34];
  cube_string[17] = temp[33];

  cube_string[35] = temp[42];
  cube_string[34] = temp[39];
  cube_string[33] = temp[36];

  cube_string[42] = temp[0];
  cube_string[39] = temp[1];
  cube_string[36] = temp[2];

  cube_string[45] = temp[51];
  cube_string[46] = temp[48];
  cube_string[47] = temp[45];
  cube_string[48] = temp[52];
  cube_string[50] = temp[46];
  cube_string[51] = temp[53];
  cube_string[52] = temp[50];
  cube_string[53] = temp[47];
  mirror_u(cube_string.substring(0, 9));
  mirror_r(cube_string.substring(9, 18));
  mirror_d(cube_string.substring(27, 36));
  mirror_l(cube_string.substring(36, 45));
  mirror_b(cube_string.substring(45));
  show_led_strip(strip_jaune, leds_b);
  show_led_strip(strip_orange, leds_l);
  show_led_strip(strip_vert, leds_d);
  show_led_strip(strip_bleu, leds_u);
  show_led_strip(strip_rouge, leds_r);
}
void rotateBPrime(String &cube_string) {
  String temp = cube_string;
  cube_string[0] = temp[42];
  cube_string[1] = temp[39];
  cube_string[2] = temp[36];

  cube_string[11] = temp[0];
  cube_string[14] = temp[1];
  cube_string[17] = temp[2];

  cube_string[35] = temp[11];
  cube_string[34] = temp[14];
  cube_string[33] = temp[17];

  cube_string[42] = temp[35];
  cube_string[39] = temp[34];
  cube_string[36] = temp[33];

  cube_string[45] = temp[47];
  cube_string[46] = temp[50];
  cube_string[47] = temp[53];
  cube_string[48] = temp[46];
  cube_string[50] = temp[52];
  cube_string[51] = temp[45];
  cube_string[52] = temp[48];
  cube_string[53] = temp[51];
  mirror_u(cube_string.substring(0, 9));
  mirror_r(cube_string.substring(9, 18));
  mirror_d(cube_string.substring(27, 36));
  mirror_l(cube_string.substring(36, 45));
  mirror_b(cube_string.substring(45));
  show_led_strip(strip_jaune, leds_b);
  show_led_strip(strip_orange, leds_l);
  show_led_strip(strip_vert, leds_d);
  show_led_strip(strip_bleu, leds_u);
  show_led_strip(strip_rouge, leds_r);
}
void rotateB2(String &cube_string) {
  String temp = cube_string;
  cube_string[0] = temp[35];
  cube_string[1] = temp[34];
  cube_string[2] = temp[33];

  cube_string[11] = temp[42];
  cube_string[14] = temp[39];
  cube_string[17] = temp[36];

  cube_string[35] = temp[0];
  cube_string[34] = temp[1];
  cube_string[33] = temp[2];

  cube_string[42] = temp[11];
  cube_string[39] = temp[14];
  cube_string[36] = temp[17];

  cube_string[45] = temp[53];
  cube_string[46] = temp[52];
  cube_string[47] = temp[51];
  cube_string[48] = temp[50];
  cube_string[50] = temp[48];
  cube_string[51] = temp[47];
  cube_string[52] = temp[46];
  cube_string[53] = temp[45];
  mirror_u(cube_string.substring(0, 9));
  mirror_r(cube_string.substring(9, 18));
  mirror_d(cube_string.substring(27, 36));
  mirror_l(cube_string.substring(36, 45));
  mirror_b(cube_string.substring(45));
  show_led_strip(strip_jaune, leds_b);
  show_led_strip(strip_orange, leds_l);
  show_led_strip(strip_vert, leds_d);
  show_led_strip(strip_bleu, leds_u);
  show_led_strip(strip_rouge, leds_r);
}
void rotateR(String &cube_string) {
  String temp = cube_string;
  cube_string[20] = temp[29];
  cube_string[23] = temp[32];
  cube_string[26] = temp[35];

  cube_string[29] = temp[51];
  cube_string[32] = temp[48];
  cube_string[35] = temp[45];

  cube_string[51] = temp[2];
  cube_string[48] = temp[5];
  cube_string[45] = temp[8];

  cube_string[2] = temp[20];
  cube_string[5] = temp[23];
  cube_string[8] = temp[26];

  cube_string[9] = temp[15];
  cube_string[10] = temp[12];
  cube_string[11] = temp[9];
  cube_string[12] = temp[16];
  cube_string[14] = temp[10];
  cube_string[15] = temp[17];
  cube_string[16] = temp[14];
  cube_string[17] = temp[11];
  mirror_u(cube_string.substring(0, 9));
  mirror_r(cube_string.substring(9, 18));
  mirror_f(cube_string.substring(18, 27));
  mirror_d(cube_string.substring(27, 36));
  mirror_b(cube_string.substring(45));
  show_led_strip(strip_jaune, leds_b);
  show_led_strip(strip_vert, leds_d);
  show_led_strip(strip_bleu, leds_u);
  show_led_strip(strip_rouge, leds_r);
}
void rotateRPrime(String &cube_string) {
  String temp = cube_string;
  cube_string[20] = temp[2];
  cube_string[23] = temp[5];
  cube_string[26] = temp[8];

  cube_string[29] = temp[20];
  cube_string[32] = temp[23];
  cube_string[35] = temp[26];

  cube_string[51] = temp[29];
  cube_string[48] = temp[32];
  cube_string[45] = temp[35];

  cube_string[2] = temp[51];
  cube_string[5] = temp[48];
  cube_string[8] = temp[45];

  cube_string[9] = temp[11];
  cube_string[10] = temp[14];
  cube_string[11] = temp[17];
  cube_string[12] = temp[10];
  cube_string[14] = temp[16];
  cube_string[15] = temp[9];
  cube_string[16] = temp[12];
  cube_string[17] = temp[15];
  mirror_u(cube_string.substring(0, 9));
  mirror_r(cube_string.substring(9, 18));
  mirror_f(cube_string.substring(18, 27));
  mirror_d(cube_string.substring(27, 36));
  mirror_b(cube_string.substring(45));
  show_led_strip(strip_jaune, leds_b);
  show_led_strip(strip_vert, leds_d);
  show_led_strip(strip_bleu, leds_u);
  show_led_strip(strip_rouge, leds_r);
}
void rotateR2(String &cube_string) {
  String temp = cube_string;
  cube_string[20] = temp[51];
  cube_string[23] = temp[48];
  cube_string[26] = temp[45];

  cube_string[29] = temp[2];
  cube_string[32] = temp[5];
  cube_string[35] = temp[8];

  cube_string[51] = temp[20];
  cube_string[48] = temp[23];
  cube_string[45] = temp[26];

  cube_string[2] = temp[29];
  cube_string[5] = temp[32];
  cube_string[8] = temp[35];

  cube_string[9] = temp[17];
  cube_string[10] = temp[16];
  cube_string[11] = temp[15];
  cube_string[12] = temp[14];
  cube_string[14] = temp[12];
  cube_string[15] = temp[11];
  cube_string[16] = temp[10];
  cube_string[17] = temp[9];
  mirror_u(cube_string.substring(0, 9));
  mirror_r(cube_string.substring(9, 18));
  mirror_f(cube_string.substring(18, 27));
  mirror_d(cube_string.substring(27, 36));
  mirror_b(cube_string.substring(45));
  show_led_strip(strip_jaune, leds_b);
  show_led_strip(strip_vert, leds_d);
  show_led_strip(strip_bleu, leds_u);
  show_led_strip(strip_rouge, leds_r);
}
void rotateL(String &cube_string) {
  String temp = cube_string;
  cube_string[18] = temp[0];
  cube_string[21] = temp[3];
  cube_string[24] = temp[6];

  cube_string[0] = temp[53];
  cube_string[3] = temp[50];
  cube_string[6] = temp[47];

  cube_string[53] = temp[27];
  cube_string[50] = temp[30];
  cube_string[47] = temp[33];

  cube_string[27] = temp[18];
  cube_string[30] = temp[21];
  cube_string[33] = temp[24];

  cube_string[36] = temp[42];
  cube_string[37] = temp[39];
  cube_string[38] = temp[36];
  cube_string[39] = temp[43];
  cube_string[41] = temp[37];
  cube_string[42] = temp[44];
  cube_string[43] = temp[41];
  cube_string[44] = temp[38];
  mirror_u(cube_string.substring(0, 9));
  mirror_f(cube_string.substring(18, 27));
  mirror_d(cube_string.substring(27, 36));
  mirror_l(cube_string.substring(36, 45));
  mirror_b(cube_string.substring(45));
  show_led_strip(strip_jaune, leds_b);
  show_led_strip(strip_orange, leds_l);
  show_led_strip(strip_vert, leds_d);
  show_led_strip(strip_bleu, leds_u);
}
void rotateLPrime(String &cube_string) {
  String temp = cube_string;
  cube_string[18] = temp[27];
  cube_string[21] = temp[30];
  cube_string[24] = temp[33];

  cube_string[0] = temp[18];
  cube_string[3] = temp[21];
  cube_string[6] = temp[24];

  cube_string[53] = temp[0];
  cube_string[50] = temp[3];
  cube_string[47] = temp[6];

  cube_string[27] = temp[53];
  cube_string[30] = temp[50];
  cube_string[33] = temp[47];

  cube_string[36] = temp[38];
  cube_string[37] = temp[41];
  cube_string[38] = temp[44];
  cube_string[39] = temp[37];
  cube_string[41] = temp[43];
  cube_string[42] = temp[36];
  cube_string[43] = temp[39];
  cube_string[44] = temp[42];
  mirror_u(cube_string.substring(0, 9));
  mirror_f(cube_string.substring(18, 27));
  mirror_d(cube_string.substring(27, 36));
  mirror_l(cube_string.substring(36, 45));
  mirror_b(cube_string.substring(45));
  show_led_strip(strip_jaune, leds_b);
  show_led_strip(strip_orange, leds_l);
  show_led_strip(strip_vert, leds_d);
  show_led_strip(strip_bleu, leds_u);
}
void rotateL2(String &cube_string) {
  String temp = cube_string;
  cube_string[18] = temp[53];
  cube_string[21] = temp[50];
  cube_string[24] = temp[47];

  cube_string[0] = temp[27];
  cube_string[3] = temp[30];
  cube_string[6] = temp[33];

  cube_string[53] = temp[18];
  cube_string[50] = temp[21];
  cube_string[47] = temp[24];

  cube_string[27] = temp[0];
  cube_string[30] = temp[3];
  cube_string[33] = temp[6];

  cube_string[36] = temp[44];
  cube_string[37] = temp[43];
  cube_string[38] = temp[42];
  cube_string[39] = temp[41];
  cube_string[41] = temp[39];
  cube_string[42] = temp[38];
  cube_string[43] = temp[37];
  cube_string[44] = temp[36];
  mirror_u(cube_string.substring(0, 9));
  mirror_f(cube_string.substring(18, 27));
  mirror_d(cube_string.substring(27, 36));
  mirror_l(cube_string.substring(36, 45));
  mirror_b(cube_string.substring(45));
  show_led_strip(strip_jaune, leds_b);
  show_led_strip(strip_orange, leds_l);
  show_led_strip(strip_vert, leds_d);
  show_led_strip(strip_bleu, leds_u);
}

// Mapping from command strings to rotation functions
RotationMapping rotationMappings[] = {
  {"U", rotateU},
  {"U'", rotateUPrime},
  {"U2", rotateU2},
  {"D", rotateD},
  {"D'", rotateDPrime},
  {"D2", rotateD2},
  {"F", rotateF},
  {"F'", rotateFPrime},
  {"F2", rotateF2},
  {"B", rotateB},
  {"B'", rotateBPrime},
  {"B2", rotateB2},
  {"R", rotateR},
  {"R'", rotateRPrime},
  {"R2", rotateR2},
  {"L", rotateL},
  {"L'", rotateLPrime},
  {"L2", rotateL2}
};

void sequence(String OPCODE, bool led_show) {
  StringSplitter *splitter = new StringSplitter(OPCODE, '-', 50);
  int itemCount = splitter->getItemCount();

  for (int i = 0; i < itemCount; i++) {
    String item = splitter->getItemAtIndex(i);
    moveAxis(item);

    if (led_show) {
      for (const auto &mapping : rotationMappings) {
        if (item == mapping.command) {
          mapping.function(cube_string);
          break; // Exit loop once function is found and called
        }
      }
    }
  }

  delete splitter;
  splitter = NULL;
}


void show_led_strip(Adafruit_NeoPixel& strip, const String& leds) {
    constexpr int LEDS_PER_FACE = 6;
    const int num_faces = min(leds.length(), LED_COUNT / LEDS_PER_FACE);

    for (int face = 0; face < num_faces; face++) {
        int r, g, b;
        switch (leds[face]) {
            case 'U': r = 0;   g = 0;   b = 255; break;
            case 'F': r = 255; g = 255; b = 255; break;
            case 'B': r = 255; g = 255; b = 0;   break;
            case 'L': r = 255; g = 100; b = 0;   break;
            case 'R': r = 255; g = 0;   b = 0;   break;
            case 'D': r = 0;   g = 255; b = 0;   break;
            default:  r = 0;   g = 0;   b = 0;   break; // Handle unexpected characters
        }

        for (int j = 0; j < LEDS_PER_FACE; j++) {
            int i = face * LEDS_PER_FACE + j;
            if (i < LED_COUNT) {
                strip.setPixelColor(i, r, g, b);
            }
        }
    }
    strip.show();
}
void mirror_f(String OPCODE){
    leds_f[0] = OPCODE[0];
    leds_f[1] = OPCODE[1];
    leds_f[2] = OPCODE[2];
    leds_f[3] = OPCODE[3];
    leds_f[4] = OPCODE[5];
    leds_f[5] = OPCODE[6];
    leds_f[6] = OPCODE[7];
    leds_f[7] = OPCODE[8];
}
void mirror_u(String OPCODE){
    leds_u[0] = OPCODE[2];
    leds_u[1] = OPCODE[5];
    leds_u[2] = OPCODE[8];
    leds_u[3] = OPCODE[7];
    leds_u[4] = OPCODE[6];
    leds_u[5] = OPCODE[3];
    leds_u[6] = OPCODE[0];
    leds_u[7] = OPCODE[1];
}
void mirror_d(String OPCODE){
    leds_d[0] = OPCODE[6];
    leds_d[1] = OPCODE[3];
    leds_d[2] = OPCODE[0];
    leds_d[3] = OPCODE[1];
    leds_d[4] = OPCODE[2];
    leds_d[5] = OPCODE[5];
    leds_d[6] = OPCODE[8];
    leds_d[7] = OPCODE[7];
}
void mirror_r(String OPCODE){
    leds_r[0] = OPCODE[2];
    leds_r[1] = OPCODE[1];
    leds_r[2] = OPCODE[0];
    leds_r[3] = OPCODE[3];
    leds_r[4] = OPCODE[6];
    leds_r[5] = OPCODE[7];
    leds_r[6] = OPCODE[8];
    leds_r[7] = OPCODE[5];
}
void mirror_l(String OPCODE){
    leds_l[0] = OPCODE[8];
    leds_l[1] = OPCODE[5];
    leds_l[2] = OPCODE[2];
    leds_l[3] = OPCODE[1];
    leds_l[4] = OPCODE[0];
    leds_l[5] = OPCODE[3];
    leds_l[6] = OPCODE[6];
    leds_l[7] = OPCODE[7];
}
void mirror_b(String OPCODE){
    leds_b[0] = OPCODE[8];
    leds_b[1] = OPCODE[7];
    leds_b[2] = OPCODE[6];
    leds_b[3] = OPCODE[3];
    leds_b[4] = OPCODE[0];
    leds_b[5] = OPCODE[1];
    leds_b[6] = OPCODE[2];
    leds_b[7] = OPCODE[5];
}


void lights(String OPCODE) {
    if (OPCODE == "RECO")
    {
        for(int i=0; i<LED_COUNT; i++) {
            strip_vert.setPixelColor(i, 255, 255, 255);
            strip_bleu.setPixelColor(i, 255, 255, 255);
            strip_jaune.setPixelColor(i, 255, 255, 255);
            strip_rouge.setPixelColor(i, 255, 255, 255);
            strip_orange.setPixelColor(i, 255, 255, 255);
        }
    }
    else if (OPCODE == "SOLV")
    {
        for(int i=0; i<LED_COUNT; i++) {
            strip_vert.setPixelColor(i, 0, 255, 0);
            strip_bleu.setPixelColor(i, 0, 0, 255);
            strip_jaune.setPixelColor(i, 255, 255, 0);
            strip_rouge.setPixelColor(i, 255, 0, 0);
            strip_orange.setPixelColor(i, 255, 100, 0);
        }
    }
    else if (OPCODE == "FLAS")
    {
        for(int i=0; i<LED_COUNT; i++) {
            strip_vert.setPixelColor(i, 0, 0, 255);
            strip_bleu.setPixelColor(i, 0, 0, 255);
            strip_jaune.setPixelColor(i, 0, 0, 255);
            strip_rouge.setPixelColor(i, 0, 0, 255);
            strip_orange.setPixelColor(i, 0, 0, 255);
        }
    }
        else if (OPCODE == "CALI")
    {
        for(int i=0; i<LED_COUNT; i++) {
            strip_vert.setPixelColor(i, 255, 0, 0);
            strip_bleu.setPixelColor(i, 255, 0, 0);
            strip_jaune.setPixelColor(i, 255, 0, 0);
            strip_rouge.setPixelColor(i, 255, 0, 0);
            strip_orange.setPixelColor(i, 255, 0, 0);
        }
    }
    strip_vert.show();
    strip_bleu.show();
    strip_rouge.show();
    strip_orange.show();
    strip_jaune.show();
}


void moveMotor(AccelStepper& motor, int steps) {
    motor.enableOutputs();
    motor.runToNewPosition(motor.currentPosition() + steps);
    motor.disableOutputs();
}

void moveAxis(String OPCODE) {
    struct AxisMove {
        String face;
        AccelStepper& motor;
    };

    const AxisMove moves[] = {
        {"U", bleu},
        {"D", vert},
        {"F", blanc},
        {"B", jaune},
        {"R", rouge},
        {"L", orange}
    };

    for (const auto& move : moves) {
        if (OPCODE == move.face) {
            moveMotor(move.motor, STEPS / 4);
            return;
        }
        if (OPCODE == move.face + "'") {
            moveMotor(move.motor, -STEPS / 4);
            return;
        }
        if (OPCODE == move.face + "2") {
            moveMotor(move.motor, STEPS / 2);
            return;
        }
    }
}

void set_speed(String OP_CODE){
    MOTOR_SPEED = OP_CODE.toInt();
    jaune.setMaxSpeed(MOTOR_SPEED);
    blanc.setMaxSpeed(MOTOR_SPEED);
    rouge.setMaxSpeed(MOTOR_SPEED);
    orange.setMaxSpeed(MOTOR_SPEED);
    vert.setMaxSpeed(MOTOR_SPEED);
    bleu.setMaxSpeed(MOTOR_SPEED);
}

void set_acceleration(String OP_CODE){
    MOTOR_ACC = OP_CODE.toInt();
    jaune.setAcceleration(MOTOR_ACC);
    blanc.setAcceleration(MOTOR_ACC);
    rouge.setAcceleration(MOTOR_ACC);
    orange.setAcceleration(MOTOR_ACC);
    vert.setAcceleration(MOTOR_ACC);
    bleu.setAcceleration(MOTOR_ACC);
}

void serial_switch(String OP_CODE){
  OP_CODE.toUpperCase();
  if (OP_CODE.length() <= 3){
      moveAxis(OP_CODE);
  }
  else if (OP_CODE.substring(0, 4) == "LEDS"){
      lights(OP_CODE.substring(5));
  }
  else if (OP_CODE.substring(0, 4) == "LEDP"){
      leds_power(OP_CODE.substring(5));
  }
  else if (OP_CODE.substring(0, 4) == "SOLV"){
      sequence(OP_CODE.substring(5), true);
  }
  else if (OP_CODE.substring(0, 4) == "MOVE"){
      sequence(OP_CODE.substring(5), false);
  }
  else if (OP_CODE.substring(0, 4) == "SPEE"){
      set_speed(OP_CODE.substring(5));
  }
  else if (OP_CODE.substring(0, 4) == "ACCE"){
      set_acceleration(OP_CODE.substring(5));
  }
  else if (OP_CODE.substring(0, 4) == "MIRR"){
      cube_string = OP_CODE.substring(5);
      mirror_u(OP_CODE.substring(5,14));
      mirror_r(OP_CODE.substring(14,23));
      mirror_f(OP_CODE.substring(23,32));
      mirror_d(OP_CODE.substring(32,41));
      mirror_l(OP_CODE.substring(41,50));
      mirror_b(OP_CODE.substring(50));
      show_led_strip(strip_jaune, leds_b);
      show_led_strip(strip_orange, leds_l);
      show_led_strip(strip_vert, leds_d);
      show_led_strip(strip_bleu, leds_u);
      show_led_strip(strip_rouge, leds_r);
  }
  Serial3.println("OK");
  Serial3.flush();
}

void loop()
{
    while (Serial3.available() > 0) {
        char receivedChar = Serial3.read();
        if (receivedChar == '\n') {
            serial_switch(OP_CODE);
            OP_CODE = "";
        } else {
            OP_CODE += receivedChar;
        }
    }

}
