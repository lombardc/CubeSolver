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

float MOTOR_SPEED = 3800.0; //3500 // good lub, 5500
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
    // for(int i=0; i<LED_COUNT; i++) {
    //     strip_vert.setPixelColor(i, 255, 0, 0);
    //     strip_bleu.setPixelColor(i, 255, 0, 0);
    //     strip_jaune.setPixelColor(i, 255, 0, 0);
    //     strip_rouge.setPixelColor(i, 255, 0, 0);
    //     strip_orange.setPixelColor(i, 255, 0, 0);
    // }
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


void sequence(String OPCODE, bool led_show){
  StringSplitter *splitter = new StringSplitter(OPCODE, '-', 50);  // new StringSplitter(string_to_split, delimiter, limit)
  int itemCount = splitter->getItemCount();
  for(int i = 0; i < itemCount; i++){
    String item = splitter->getItemAtIndex(i);
    moveAxis(item);
    if (led_show){
        char temp_buffer[54];
        strcpy(temp_buffer, cube_string.c_str());
        String cube_temp = String(temp_buffer);
        if (item=="U"){
          cube_string[18] = cube_temp[9];
          cube_string[19] = cube_temp[10];
          cube_string[20] = cube_temp[11];

          cube_string[36] = cube_temp[18];
          cube_string[37] = cube_temp[19];
          cube_string[38] = cube_temp[20];

          cube_string[45] = cube_temp[36];
          cube_string[46] = cube_temp[37];
          cube_string[47] = cube_temp[38];

          cube_string[9] = cube_temp[45];
          cube_string[10] = cube_temp[46];
          cube_string[11] = cube_temp[47];

          cube_string[0] = cube_temp[6];
          cube_string[1] = cube_temp[3];
          cube_string[2] = cube_temp[0];
          cube_string[3] = cube_temp[7];
          cube_string[5] = cube_temp[1];
          cube_string[6] = cube_temp[8];
          cube_string[7] = cube_temp[5];
          cube_string[8] = cube_temp[2];
        }
        else if (item=="U'"){
          cube_string[18] = cube_temp[36];
          cube_string[19] = cube_temp[37];
          cube_string[20] = cube_temp[38];

          cube_string[36] = cube_temp[45];
          cube_string[37] = cube_temp[46];
          cube_string[38] = cube_temp[47];

          cube_string[45] = cube_temp[9];
          cube_string[46] = cube_temp[10];
          cube_string[47] = cube_temp[11];

          cube_string[9] = cube_temp[18];
          cube_string[10] = cube_temp[19];
          cube_string[11] = cube_temp[20];

          cube_string[0] = cube_temp[2];
          cube_string[1] = cube_temp[5];
          cube_string[2] = cube_temp[8];
          cube_string[3] = cube_temp[1];
          cube_string[5] = cube_temp[7];
          cube_string[6] = cube_temp[0];
          cube_string[7] = cube_temp[3];
          cube_string[8] = cube_temp[6];
        }
        else if (item=="U2"){
          cube_string[18] = cube_temp[45];
          cube_string[19] = cube_temp[46];
          cube_string[20] = cube_temp[47];

          cube_string[36] = cube_temp[9];
          cube_string[37] = cube_temp[10];
          cube_string[38] = cube_temp[11];

          cube_string[45] = cube_temp[18];
          cube_string[46] = cube_temp[19];
          cube_string[47] = cube_temp[20];

          cube_string[9] = cube_temp[36];
          cube_string[10] = cube_temp[37];
          cube_string[11] = cube_temp[38];

          cube_string[8] = cube_temp[0];
          cube_string[7] = cube_temp[1];
          cube_string[6] = cube_temp[2];
          cube_string[5] = cube_temp[3];
          cube_string[3] = cube_temp[5];
          cube_string[2] = cube_temp[6];
          cube_string[1] = cube_temp[7];
          cube_string[0] = cube_temp[8];
        }
        else if (item=="D"){
          cube_string[24] = cube_temp[42];
          cube_string[25] = cube_temp[43];
          cube_string[26] = cube_temp[44];

          cube_string[42] = cube_temp[51];
          cube_string[43] = cube_temp[52];
          cube_string[44] = cube_temp[53];

          cube_string[51] = cube_temp[15];
          cube_string[52] = cube_temp[16];
          cube_string[53] = cube_temp[17];

          cube_string[15] = cube_temp[24];
          cube_string[16] = cube_temp[25];
          cube_string[17] = cube_temp[26];

          cube_string[27] = cube_temp[33];
          cube_string[28] = cube_temp[30];
          cube_string[29] = cube_temp[27];
          cube_string[30] = cube_temp[34];
          cube_string[32] = cube_temp[28];
          cube_string[33] = cube_temp[35];
          cube_string[34] = cube_temp[32];
          cube_string[35] = cube_temp[29];
        }
        else if (item=="D'"){
          cube_string[24] = cube_temp[15];
          cube_string[25] = cube_temp[16];
          cube_string[26] = cube_temp[17];

          cube_string[42] = cube_temp[24];
          cube_string[43] = cube_temp[25];
          cube_string[44] = cube_temp[26];

          cube_string[51] = cube_temp[42];
          cube_string[52] = cube_temp[43];
          cube_string[53] = cube_temp[44];

          cube_string[15] = cube_temp[51];
          cube_string[16] = cube_temp[52];
          cube_string[17] = cube_temp[53];

          cube_string[27] = cube_temp[29];
          cube_string[28] = cube_temp[32];
          cube_string[29] = cube_temp[35];
          cube_string[30] = cube_temp[28];
          cube_string[32] = cube_temp[34];
          cube_string[33] = cube_temp[27];
          cube_string[34] = cube_temp[30];
          cube_string[35] = cube_temp[33];
        }
        else if (item=="D2"){
          cube_string[24] = cube_temp[51];
          cube_string[25] = cube_temp[52];
          cube_string[26] = cube_temp[53];

          cube_string[42] = cube_temp[15];
          cube_string[43] = cube_temp[16];
          cube_string[44] = cube_temp[17];

          cube_string[51] = cube_temp[24];
          cube_string[52] = cube_temp[25];
          cube_string[53] = cube_temp[26];

          cube_string[15] = cube_temp[42];
          cube_string[16] = cube_temp[43];
          cube_string[17] = cube_temp[44];

          cube_string[27] = cube_temp[35];
          cube_string[28] = cube_temp[34];
          cube_string[29] = cube_temp[33];
          cube_string[30] = cube_temp[32];
          cube_string[32] = cube_temp[30];
          cube_string[33] = cube_temp[29];
          cube_string[34] = cube_temp[28];
          cube_string[35] = cube_temp[27];
        }
        else if (item=="F"){
          cube_string[6] = cube_temp[44];
          cube_string[7] = cube_temp[41];
          cube_string[8] = cube_temp[38];

          cube_string[44] = cube_temp[29];
          cube_string[41] = cube_temp[28];
          cube_string[38] = cube_temp[27];

          cube_string[29] = cube_temp[9];
          cube_string[28] = cube_temp[12];
          cube_string[27] = cube_temp[15];

          cube_string[9] = cube_temp[6];
          cube_string[12] = cube_temp[7];
          cube_string[15] = cube_temp[8];

          cube_string[18] = cube_temp[24];
          cube_string[19] = cube_temp[21];
          cube_string[20] = cube_temp[18];
          cube_string[21] = cube_temp[25];
          cube_string[23] = cube_temp[19];
          cube_string[24] = cube_temp[26];
          cube_string[25] = cube_temp[23];
          cube_string[26] = cube_temp[20];
        }
        else if (item=="F'"){
          cube_string[6] = cube_temp[9];
          cube_string[7] = cube_temp[12];
          cube_string[8] = cube_temp[15];

          cube_string[44] = cube_temp[6];
          cube_string[41] = cube_temp[7];
          cube_string[38] = cube_temp[8];

          cube_string[29] = cube_temp[44];
          cube_string[28] = cube_temp[41];
          cube_string[27] = cube_temp[38];

          cube_string[9] = cube_temp[29];
          cube_string[12] = cube_temp[28];
          cube_string[15] = cube_temp[27];

          cube_string[18] = cube_temp[20];
          cube_string[19] = cube_temp[23];
          cube_string[20] = cube_temp[26];
          cube_string[21] = cube_temp[19];
          cube_string[23] = cube_temp[25];
          cube_string[24] = cube_temp[18];
          cube_string[25] = cube_temp[21];
          cube_string[26] = cube_temp[24];
        }
        else if (item=="F2"){
          cube_string[6] = cube_temp[29];
          cube_string[7] = cube_temp[28];
          cube_string[8] = cube_temp[27];

          cube_string[44] = cube_temp[9];
          cube_string[41] = cube_temp[12];
          cube_string[38] = cube_temp[15];

          cube_string[29] = cube_temp[6];
          cube_string[28] = cube_temp[7];
          cube_string[27] = cube_temp[8];

          cube_string[9] = cube_temp[44];
          cube_string[12] = cube_temp[41];
          cube_string[15] = cube_temp[38];

          cube_string[18] = cube_temp[26];
          cube_string[19] = cube_temp[25];
          cube_string[20] = cube_temp[24];
          cube_string[21] = cube_temp[23];
          cube_string[23] = cube_temp[21];
          cube_string[24] = cube_temp[20];
          cube_string[25] = cube_temp[19];
          cube_string[26] = cube_temp[18];
        }
        else if (item=="B"){
          cube_string[0] = cube_temp[11];
          cube_string[1] = cube_temp[14];
          cube_string[2] = cube_temp[17];

          cube_string[11] = cube_temp[35];
          cube_string[14] = cube_temp[34];
          cube_string[17] = cube_temp[33];

          cube_string[35] = cube_temp[42];
          cube_string[34] = cube_temp[39];
          cube_string[33] = cube_temp[36];

          cube_string[42] = cube_temp[0];
          cube_string[39] = cube_temp[1];
          cube_string[36] = cube_temp[2];

          cube_string[45] = cube_temp[51];
          cube_string[46] = cube_temp[48];
          cube_string[47] = cube_temp[45];
          cube_string[48] = cube_temp[52];
          cube_string[50] = cube_temp[46];
          cube_string[51] = cube_temp[53];
          cube_string[52] = cube_temp[50];
          cube_string[53] = cube_temp[47];
        }
        else if (item=="B'"){
          cube_string[0] = cube_temp[42];
          cube_string[1] = cube_temp[39];
          cube_string[2] = cube_temp[36];

          cube_string[11] = cube_temp[0];
          cube_string[14] = cube_temp[1];
          cube_string[17] = cube_temp[2];

          cube_string[35] = cube_temp[11];
          cube_string[34] = cube_temp[14];
          cube_string[33] = cube_temp[17];

          cube_string[42] = cube_temp[35];
          cube_string[39] = cube_temp[34];
          cube_string[36] = cube_temp[33];

          cube_string[45] = cube_temp[47];
          cube_string[46] = cube_temp[50];
          cube_string[47] = cube_temp[53];
          cube_string[48] = cube_temp[46];
          cube_string[50] = cube_temp[52];
          cube_string[51] = cube_temp[45];
          cube_string[52] = cube_temp[48];
          cube_string[53] = cube_temp[51];
        }
        else if (item=="B2"){
          cube_string[0] = cube_temp[35];
          cube_string[1] = cube_temp[34];
          cube_string[2] = cube_temp[33];

          cube_string[11] = cube_temp[42];
          cube_string[14] = cube_temp[39];
          cube_string[17] = cube_temp[36];

          cube_string[35] = cube_temp[0];
          cube_string[34] = cube_temp[1];
          cube_string[33] = cube_temp[2];

          cube_string[42] = cube_temp[11];
          cube_string[39] = cube_temp[14];
          cube_string[36] = cube_temp[17];

          cube_string[45] = cube_temp[53];
          cube_string[46] = cube_temp[52];
          cube_string[47] = cube_temp[51];
          cube_string[48] = cube_temp[50];
          cube_string[50] = cube_temp[48];
          cube_string[51] = cube_temp[47];
          cube_string[52] = cube_temp[46];
          cube_string[53] = cube_temp[45];
        }
        else if (item=="R"){
          cube_string[20] = cube_temp[29];
          cube_string[23] = cube_temp[32];
          cube_string[26] = cube_temp[35];

          cube_string[29] = cube_temp[51];
          cube_string[32] = cube_temp[48];
          cube_string[35] = cube_temp[45];

          cube_string[51] = cube_temp[2];
          cube_string[48] = cube_temp[5];
          cube_string[45] = cube_temp[8];

          cube_string[2] = cube_temp[20];
          cube_string[5] = cube_temp[23];
          cube_string[8] = cube_temp[26];

          cube_string[9] = cube_temp[15];
          cube_string[10] = cube_temp[12];
          cube_string[11] = cube_temp[9];
          cube_string[12] = cube_temp[16];
          cube_string[14] = cube_temp[10];
          cube_string[15] = cube_temp[17];
          cube_string[16] = cube_temp[14];
          cube_string[17] = cube_temp[11];
        }
        else if (item=="R'"){
          cube_string[20] = cube_temp[2];
          cube_string[23] = cube_temp[5];
          cube_string[26] = cube_temp[8];

          cube_string[29] = cube_temp[20];
          cube_string[32] = cube_temp[23];
          cube_string[35] = cube_temp[26];

          cube_string[51] = cube_temp[29];
          cube_string[48] = cube_temp[32];
          cube_string[45] = cube_temp[35];

          cube_string[2] = cube_temp[51];
          cube_string[5] = cube_temp[48];
          cube_string[8] = cube_temp[45];

          cube_string[9] = cube_temp[11];
          cube_string[10] = cube_temp[14];
          cube_string[11] = cube_temp[17];
          cube_string[12] = cube_temp[10];
          cube_string[14] = cube_temp[16];
          cube_string[15] = cube_temp[9];
          cube_string[16] = cube_temp[12];
          cube_string[17] = cube_temp[15];
        }
        else if (item=="R2"){
          cube_string[20] = cube_temp[51];
          cube_string[23] = cube_temp[48];
          cube_string[26] = cube_temp[45];

          cube_string[29] = cube_temp[2];
          cube_string[32] = cube_temp[5];
          cube_string[35] = cube_temp[8];

          cube_string[51] = cube_temp[20];
          cube_string[48] = cube_temp[23];
          cube_string[45] = cube_temp[26];

          cube_string[2] = cube_temp[29];
          cube_string[5] = cube_temp[32];
          cube_string[8] = cube_temp[35];

          cube_string[9] = cube_temp[17];
          cube_string[10] = cube_temp[16];
          cube_string[11] = cube_temp[15];
          cube_string[12] = cube_temp[14];
          cube_string[14] = cube_temp[12];
          cube_string[15] = cube_temp[11];
          cube_string[16] = cube_temp[10];
          cube_string[17] = cube_temp[9];
        }
        else if (item=="L"){
          cube_string[18] = cube_temp[0];
          cube_string[21] = cube_temp[3];
          cube_string[24] = cube_temp[6];

          cube_string[0] = cube_temp[53];
          cube_string[3] = cube_temp[50];
          cube_string[6] = cube_temp[47];

          cube_string[53] = cube_temp[27];
          cube_string[50] = cube_temp[30];
          cube_string[47] = cube_temp[33];

          cube_string[27] = cube_temp[18];
          cube_string[30] = cube_temp[21];
          cube_string[33] = cube_temp[24];

          cube_string[36] = cube_temp[42];
          cube_string[37] = cube_temp[39];
          cube_string[38] = cube_temp[36];
          cube_string[39] = cube_temp[43];
          cube_string[41] = cube_temp[37];
          cube_string[42] = cube_temp[44];
          cube_string[43] = cube_temp[41];
          cube_string[44] = cube_temp[38];
        }
        else if (item=="L'"){
          cube_string[18] = cube_temp[27];
          cube_string[21] = cube_temp[30];
          cube_string[24] = cube_temp[33];

          cube_string[0] = cube_temp[18];
          cube_string[3] = cube_temp[21];
          cube_string[6] = cube_temp[24];

          cube_string[53] = cube_temp[0];
          cube_string[50] = cube_temp[3];
          cube_string[47] = cube_temp[6];

          cube_string[27] = cube_temp[53];
          cube_string[30] = cube_temp[50];
          cube_string[33] = cube_temp[47];

          cube_string[36] = cube_temp[38];
          cube_string[37] = cube_temp[41];
          cube_string[38] = cube_temp[44];
          cube_string[39] = cube_temp[37];
          cube_string[41] = cube_temp[43];
          cube_string[42] = cube_temp[36];
          cube_string[43] = cube_temp[39];
          cube_string[44] = cube_temp[42];
        }
        else if (item=="L2"){
          cube_string[18] = cube_temp[53];
          cube_string[21] = cube_temp[50];
          cube_string[24] = cube_temp[47];

          cube_string[0] = cube_temp[27];
          cube_string[3] = cube_temp[30];
          cube_string[6] = cube_temp[33];

          cube_string[53] = cube_temp[18];
          cube_string[50] = cube_temp[21];
          cube_string[47] = cube_temp[24];

          cube_string[27] = cube_temp[0];
          cube_string[30] = cube_temp[3];
          cube_string[33] = cube_temp[6];

          cube_string[36] = cube_temp[44];
          cube_string[37] = cube_temp[43];
          cube_string[38] = cube_temp[42];
          cube_string[39] = cube_temp[41];
          cube_string[41] = cube_temp[39];
          cube_string[42] = cube_temp[38];
          cube_string[43] = cube_temp[37];
          cube_string[44] = cube_temp[36];
        }
        mirror_u(cube_string.substring(0,9));
        mirror_r(cube_string.substring(9,18));
        mirror_f(cube_string.substring(18,27));
        mirror_d(cube_string.substring(27,36));
        mirror_l(cube_string.substring(36,45));
        mirror_b(cube_string.substring(45));
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
    show_led_strip(strip_bleu, leds_u);
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
    show_led_strip(strip_vert, leds_d);
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
    show_led_strip(strip_rouge, leds_r);
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
    show_led_strip(strip_orange, leds_l);
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
    show_led_strip(strip_jaune, leds_b);
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
  else if (OP_CODE.substring(0, 4) == "MIRR"){
      cube_string = OP_CODE.substring(5);
      mirror_u(OP_CODE.substring(5,14));
      mirror_r(OP_CODE.substring(14,23));
      mirror_f(OP_CODE.substring(23,32));
      mirror_d(OP_CODE.substring(32,41));
      mirror_l(OP_CODE.substring(41,50));
      mirror_b(OP_CODE.substring(50));
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
