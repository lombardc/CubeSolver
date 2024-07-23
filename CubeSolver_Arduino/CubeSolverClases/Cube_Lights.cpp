// Cube_Lights.cpp
#include "Cube_Lights.h"

Cube_Lights::Cube_Lights(LED_Array& UP, LED_Array& DOWN, LED_Array& RIGHT, LED_Array& LEFT, LED_Array& BACK) 
    : up(UP), down(DOWN), right(RIGHT), left(LEFT), back(BACK) {
    cube_string = "UUUUUUUUURRRRRRRRRFFFFFFFFFDDDDDDDDDLLLLLLLLLBBBBBBBBB";
}

void Cube_Lights::setBrightness(int brightness) {
    up.setBrightness(brightness);
    down.setBrightness(brightness);
    right.setBrightness(brightness);
    left.setBrightness(brightness);
    back.setBrightness(brightness);
}

void Cube_Lights::setColor(int r, int g, int b) {
    up.setColor(r, g, b);
    down.setColor(r, g, b);
    right.setColor(r, g, b);
    left.setColor(r, g, b);
    back.setColor(r, g, b);
}

void Cube_Lights::setCubeString(String Cube_String){
    this->cube_string = Cube_String;
}

void Cube_Lights::resetCubeString(){
    this->cube_string = "UUUUUUUUURRRRRRRRRFFFFFFFFFDDDDDDDDDLLLLLLLLLBBBBBBBBB";
}


void Cube_Lights::setMirror(){
    up.mirror(this->cube_string.substring(0, 9));
    right.mirror(this->cube_string.substring(9, 18));
    down.mirror(this->cube_string.substring(27, 36));
    left.mirror(this->cube_string.substring(36, 45));
    back.mirror(this->cube_string.substring(45, 54));
}

using RotateFunction = void (*)(String&);

// Define the structure for rotation mappings
struct RotationMapping {
    const char* command;
    void (Cube_Lights::*function)();
};

// Define the array of rotation mappings
RotationMapping rotationMappings[] = {
    {"U", &Cube_Lights::rotateU},
    {"U'", &Cube_Lights::rotateUPrime},
    {"U2", &Cube_Lights::rotateU2},
    {"D", &Cube_Lights::rotateD},
    {"D'", &Cube_Lights::rotateDPrime},
    {"D2", &Cube_Lights::rotateD2},
    {"F", &Cube_Lights::rotateF},
    {"F'", &Cube_Lights::rotateFPrime},
    {"F2", &Cube_Lights::rotateF2},
    {"B", &Cube_Lights::rotateB},
    {"B'", &Cube_Lights::rotateBPrime},
    {"B2", &Cube_Lights::rotateB2},
    {"R", &Cube_Lights::rotateR},
    {"R'", &Cube_Lights::rotateRPrime},
    {"R2", &Cube_Lights::rotateR2},
    {"L", &Cube_Lights::rotateL},
    {"L'", &Cube_Lights::rotateLPrime},
    {"L2", &Cube_Lights::rotateL2}
};

void Cube_Lights::rotate(String move) {
    for (const auto &mapping : rotationMappings) {
        if (move == mapping.command) {
            (this->*(mapping.function))();
            break;
        }
    }
}

void Cube_Lights::rotateU() {
    String temp = this->cube_string;
    this->cube_string[18] = temp[9];
    this->cube_string[19] = temp[10];
    this->cube_string[20] = temp[11];

    this->cube_string[36] = temp[18];
    this->cube_string[37] = temp[19];
    this->cube_string[38] = temp[20];

    this->cube_string[45] = temp[36];
    this->cube_string[46] = temp[37];
    this->cube_string[47] = temp[38];

    this->cube_string[9] = temp[45];
    this->cube_string[10] = temp[46];
    this->cube_string[11] = temp[47];

    this->cube_string[0] = temp[6];
    this->cube_string[1] = temp[3];
    this->cube_string[2] = temp[0];
    this->cube_string[3] = temp[7];
    this->cube_string[5] = temp[1];
    this->cube_string[6] = temp[8];
    this->cube_string[7] = temp[5];
    this->cube_string[8] = temp[2];
    
    setMirror();
}

void Cube_Lights::rotateUPrime() {
  String temp = this->cube_string;
  this->cube_string[18] = temp[36];
  this->cube_string[19] = temp[37];
  this->cube_string[20] = temp[38];

  this->cube_string[36] = temp[45];
  this->cube_string[37] = temp[46];
  this->cube_string[38] = temp[47];

  this->cube_string[45] = temp[9];
  this->cube_string[46] = temp[10];
  this->cube_string[47] = temp[11];

  this->cube_string[9] = temp[18];
  this->cube_string[10] = temp[19];
  this->cube_string[11] = temp[20];

  this->cube_string[0] = temp[2];
  this->cube_string[1] = temp[5];
  this->cube_string[2] = temp[8];
  this->cube_string[3] = temp[1];
  this->cube_string[5] = temp[7];
  this->cube_string[6] = temp[0];
  this->cube_string[7] = temp[3];
  this->cube_string[8] = temp[6];

  setMirror();
}
void Cube_Lights::rotateU2() {
  String temp = this->cube_string;
  this->cube_string[18] = temp[45];
  this->cube_string[19] = temp[46];
  this->cube_string[20] = temp[47];

  this->cube_string[36] = temp[9];
  this->cube_string[37] = temp[10];
  this->cube_string[38] = temp[11];

  this->cube_string[45] = temp[18];
  this->cube_string[46] = temp[19];
  this->cube_string[47] = temp[20];

  this->cube_string[9] = temp[36];
  this->cube_string[10] = temp[37];
  this->cube_string[11] = temp[38];

  this->cube_string[8] = temp[0];
  this->cube_string[7] = temp[1];
  this->cube_string[6] = temp[2];
  this->cube_string[5] = temp[3];
  this->cube_string[3] = temp[5];
  this->cube_string[2] = temp[6];
  this->cube_string[1] = temp[7];
  this->cube_string[0] = temp[8];

  setMirror();
}
void Cube_Lights::rotateD() {
  String temp = this->cube_string;
  this->cube_string[24] = temp[42];
  this->cube_string[25] = temp[43];
  this->cube_string[26] = temp[44];

  this->cube_string[42] = temp[51];
  this->cube_string[43] = temp[52];
  this->cube_string[44] = temp[53];

  this->cube_string[51] = temp[15];
  this->cube_string[52] = temp[16];
  this->cube_string[53] = temp[17];

  this->cube_string[15] = temp[24];
  this->cube_string[16] = temp[25];
  this->cube_string[17] = temp[26];

  this->cube_string[27] = temp[33];
  this->cube_string[28] = temp[30];
  this->cube_string[29] = temp[27];
  this->cube_string[30] = temp[34];
  this->cube_string[32] = temp[28];
  this->cube_string[33] = temp[35];
  this->cube_string[34] = temp[32];
  this->cube_string[35] = temp[29];

  setMirror();
}
void Cube_Lights::rotateD2() {
  String temp = this->cube_string;
  this->cube_string[24] = temp[51];
  this->cube_string[25] = temp[52];
  this->cube_string[26] = temp[53];

  this->cube_string[42] = temp[15];
  this->cube_string[43] = temp[16];
  this->cube_string[44] = temp[17];

  this->cube_string[51] = temp[24];
  this->cube_string[52] = temp[25];
  this->cube_string[53] = temp[26];

  this->cube_string[15] = temp[42];
  this->cube_string[16] = temp[43];
  this->cube_string[17] = temp[44];

  this->cube_string[27] = temp[35];
  this->cube_string[28] = temp[34];
  this->cube_string[29] = temp[33];
  this->cube_string[30] = temp[32];
  this->cube_string[32] = temp[30];
  this->cube_string[33] = temp[29];
  this->cube_string[34] = temp[28];
  this->cube_string[35] = temp[27];

  setMirror();
}
void Cube_Lights::rotateDPrime() {
  String temp = this->cube_string;
  this->cube_string[24] = temp[15];
  this->cube_string[25] = temp[16];
  this->cube_string[26] = temp[17];

  this->cube_string[42] = temp[24];
  this->cube_string[43] = temp[25];
  this->cube_string[44] = temp[26];

  this->cube_string[51] = temp[42];
  this->cube_string[52] = temp[43];
  this->cube_string[53] = temp[44];

  this->cube_string[15] = temp[51];
  this->cube_string[16] = temp[52];
  this->cube_string[17] = temp[53];

  this->cube_string[27] = temp[29];
  this->cube_string[28] = temp[32];
  this->cube_string[29] = temp[35];
  this->cube_string[30] = temp[28];
  this->cube_string[32] = temp[34];
  this->cube_string[33] = temp[27];
  this->cube_string[34] = temp[30];
  this->cube_string[35] = temp[33];

  setMirror();
}
void Cube_Lights::rotateF() {
  String temp = this->cube_string;
  this->cube_string[6] = temp[44];
  this->cube_string[7] = temp[41];
  this->cube_string[8] = temp[38];

  this->cube_string[44] = temp[29];
  this->cube_string[41] = temp[28];
  this->cube_string[38] = temp[27];

  this->cube_string[29] = temp[9];
  this->cube_string[28] = temp[12];
  this->cube_string[27] = temp[15];

  this->cube_string[9] = temp[6];
  this->cube_string[12] = temp[7];
  this->cube_string[15] = temp[8];

  this->cube_string[18] = temp[24];
  this->cube_string[19] = temp[21];
  this->cube_string[20] = temp[18];
  this->cube_string[21] = temp[25];
  this->cube_string[23] = temp[19];
  this->cube_string[24] = temp[26];
  this->cube_string[25] = temp[23];
  this->cube_string[26] = temp[20];

  setMirror();
}
void Cube_Lights::rotateFPrime() {
  String temp = this->cube_string;  
  this->cube_string[6] = temp[9];
  this->cube_string[7] = temp[12];
  this->cube_string[8] = temp[15];

  this->cube_string[44] = temp[6];
  this->cube_string[41] = temp[7];
  this->cube_string[38] = temp[8];

  this->cube_string[29] = temp[44];
  this->cube_string[28] = temp[41];
  this->cube_string[27] = temp[38];

  this->cube_string[9] = temp[29];
  this->cube_string[12] = temp[28];
  this->cube_string[15] = temp[27];

  this->cube_string[18] = temp[20];
  this->cube_string[19] = temp[23];
  this->cube_string[20] = temp[26];
  this->cube_string[21] = temp[19];
  this->cube_string[23] = temp[25];
  this->cube_string[24] = temp[18];
  this->cube_string[25] = temp[21];
  this->cube_string[26] = temp[24];

  setMirror();
}
void Cube_Lights::rotateF2() {
  String temp = this->cube_string;
  this->cube_string[6] = temp[29];
  this->cube_string[7] = temp[28];
  this->cube_string[8] = temp[27];

  this->cube_string[44] = temp[9];
  this->cube_string[41] = temp[12];
  this->cube_string[38] = temp[15];

  this->cube_string[29] = temp[6];
  this->cube_string[28] = temp[7];
  this->cube_string[27] = temp[8];

  this->cube_string[9] = temp[44];
  this->cube_string[12] = temp[41];
  this->cube_string[15] = temp[38];

  this->cube_string[18] = temp[26];
  this->cube_string[19] = temp[25];
  this->cube_string[20] = temp[24];
  this->cube_string[21] = temp[23];
  this->cube_string[23] = temp[21];
  this->cube_string[24] = temp[20];
  this->cube_string[25] = temp[19];
  this->cube_string[26] = temp[18];

  setMirror();
}
void Cube_Lights::rotateB() {
  String temp = this->cube_string;
  this->cube_string[0] = temp[11];
  this->cube_string[1] = temp[14];
  this->cube_string[2] = temp[17];

  this->cube_string[11] = temp[35];
  this->cube_string[14] = temp[34];
  this->cube_string[17] = temp[33];

  this->cube_string[35] = temp[42];
  this->cube_string[34] = temp[39];
  this->cube_string[33] = temp[36];

  this->cube_string[42] = temp[0];
  this->cube_string[39] = temp[1];
  this->cube_string[36] = temp[2];

  this->cube_string[45] = temp[51];
  this->cube_string[46] = temp[48];
  this->cube_string[47] = temp[45];
  this->cube_string[48] = temp[52];
  this->cube_string[50] = temp[46];
  this->cube_string[51] = temp[53];
  this->cube_string[52] = temp[50];
  this->cube_string[53] = temp[47];

  setMirror();
}
void Cube_Lights::rotateBPrime() {
  String temp = this->cube_string;
  this->cube_string[0] = temp[42];
  this->cube_string[1] = temp[39];
  this->cube_string[2] = temp[36];

  this->cube_string[11] = temp[0];
  this->cube_string[14] = temp[1];
  this->cube_string[17] = temp[2];

  this->cube_string[35] = temp[11];
  this->cube_string[34] = temp[14];
  this->cube_string[33] = temp[17];

  this->cube_string[42] = temp[35];
  this->cube_string[39] = temp[34];
  this->cube_string[36] = temp[33];

  this->cube_string[45] = temp[47];
  this->cube_string[46] = temp[50];
  this->cube_string[47] = temp[53];
  this->cube_string[48] = temp[46];
  this->cube_string[50] = temp[52];
  this->cube_string[51] = temp[45];
  this->cube_string[52] = temp[48];
  this->cube_string[53] = temp[51];

  setMirror();
}
void Cube_Lights::rotateB2() {
  String temp = this->cube_string;
  this->cube_string[0] = temp[35];
  this->cube_string[1] = temp[34];
  this->cube_string[2] = temp[33];

  this->cube_string[11] = temp[42];
  this->cube_string[14] = temp[39];
  this->cube_string[17] = temp[36];

  this->cube_string[35] = temp[0];
  this->cube_string[34] = temp[1];
  this->cube_string[33] = temp[2];

  this->cube_string[42] = temp[11];
  this->cube_string[39] = temp[14];
  this->cube_string[36] = temp[17];

  this->cube_string[45] = temp[53];
  this->cube_string[46] = temp[52];
  this->cube_string[47] = temp[51];
  this->cube_string[48] = temp[50];
  this->cube_string[50] = temp[48];
  this->cube_string[51] = temp[47];
  this->cube_string[52] = temp[46];
  this->cube_string[53] = temp[45];

  setMirror();
}
void Cube_Lights::rotateR() {
  String temp = this->cube_string;
  this->cube_string[20] = temp[29];
  this->cube_string[23] = temp[32];
  this->cube_string[26] = temp[35];

  this->cube_string[29] = temp[51];
  this->cube_string[32] = temp[48];
  this->cube_string[35] = temp[45];

  this->cube_string[51] = temp[2];
  this->cube_string[48] = temp[5];
  this->cube_string[45] = temp[8];

  this->cube_string[2] = temp[20];
  this->cube_string[5] = temp[23];
  this->cube_string[8] = temp[26];

  this->cube_string[9] = temp[15];
  this->cube_string[10] = temp[12];
  this->cube_string[11] = temp[9];
  this->cube_string[12] = temp[16];
  this->cube_string[14] = temp[10];
  this->cube_string[15] = temp[17];
  this->cube_string[16] = temp[14];
  this->cube_string[17] = temp[11];

  setMirror();
}
void Cube_Lights::rotateRPrime() {
  String temp = this->cube_string;
  this->cube_string[20] = temp[2];
  this->cube_string[23] = temp[5];
  this->cube_string[26] = temp[8];

  this->cube_string[29] = temp[20];
  this->cube_string[32] = temp[23];
  this->cube_string[35] = temp[26];

  this->cube_string[51] = temp[29];
  this->cube_string[48] = temp[32];
  this->cube_string[45] = temp[35];

  this->cube_string[2] = temp[51];
  this->cube_string[5] = temp[48];
  this->cube_string[8] = temp[45];

  this->cube_string[9] = temp[11];
  this->cube_string[10] = temp[14];
  this->cube_string[11] = temp[17];
  this->cube_string[12] = temp[10];
  this->cube_string[14] = temp[16];
  this->cube_string[15] = temp[9];
  this->cube_string[16] = temp[12];
  this->cube_string[17] = temp[15];

  setMirror();
}
void Cube_Lights::rotateR2() {
  String temp = this->cube_string;
  this->cube_string[20] = temp[51];
  this->cube_string[23] = temp[48];
  this->cube_string[26] = temp[45];

  this->cube_string[29] = temp[2];
  this->cube_string[32] = temp[5];
  this->cube_string[35] = temp[8];

  this->cube_string[51] = temp[20];
  this->cube_string[48] = temp[23];
  this->cube_string[45] = temp[26];

  this->cube_string[2] = temp[29];
  this->cube_string[5] = temp[32];
  this->cube_string[8] = temp[35];

  this->cube_string[9] = temp[17];
  this->cube_string[10] = temp[16];
  this->cube_string[11] = temp[15];
  this->cube_string[12] = temp[14];
  this->cube_string[14] = temp[12];
  this->cube_string[15] = temp[11];
  this->cube_string[16] = temp[10];
  this->cube_string[17] = temp[9];

  setMirror();
}
void Cube_Lights::rotateL() {
  String temp = this->cube_string;
  this->cube_string[18] = temp[0];
  this->cube_string[21] = temp[3];
  this->cube_string[24] = temp[6];

  this->cube_string[0] = temp[53];
  this->cube_string[3] = temp[50];
  this->cube_string[6] = temp[47];

  this->cube_string[53] = temp[27];
  this->cube_string[50] = temp[30];
  this->cube_string[47] = temp[33];

  this->cube_string[27] = temp[18];
  this->cube_string[30] = temp[21];
  this->cube_string[33] = temp[24];

  this->cube_string[36] = temp[42];
  this->cube_string[37] = temp[39];
  this->cube_string[38] = temp[36];
  this->cube_string[39] = temp[43];
  this->cube_string[41] = temp[37];
  this->cube_string[42] = temp[44];
  this->cube_string[43] = temp[41];
  this->cube_string[44] = temp[38];

  setMirror();
}
void Cube_Lights::rotateLPrime() {
  String temp = this->cube_string;
  this->cube_string[18] = temp[27];
  this->cube_string[21] = temp[30];
  this->cube_string[24] = temp[33];

  this->cube_string[0] = temp[18];
  this->cube_string[3] = temp[21];
  this->cube_string[6] = temp[24];

  this->cube_string[53] = temp[0];
  this->cube_string[50] = temp[3];
  this->cube_string[47] = temp[6];

  this->cube_string[27] = temp[53];
  this->cube_string[30] = temp[50];
  this->cube_string[33] = temp[47];

  this->cube_string[36] = temp[38];
  this->cube_string[37] = temp[41];
  this->cube_string[38] = temp[44];
  this->cube_string[39] = temp[37];
  this->cube_string[41] = temp[43];
  this->cube_string[42] = temp[36];
  this->cube_string[43] = temp[39];
  this->cube_string[44] = temp[42];

  setMirror();
}
void Cube_Lights::rotateL2() {
  String temp = this->cube_string;
  this->cube_string[18] = temp[53];
  this->cube_string[21] = temp[50];
  this->cube_string[24] = temp[47];

  this->cube_string[0] = temp[27];
  this->cube_string[3] = temp[30];
  this->cube_string[6] = temp[33];

  this->cube_string[53] = temp[18];
  this->cube_string[50] = temp[21];
  this->cube_string[47] = temp[24];

  this->cube_string[27] = temp[0];
  this->cube_string[30] = temp[3];
  this->cube_string[33] = temp[6];

  this->cube_string[36] = temp[44];
  this->cube_string[37] = temp[43];
  this->cube_string[38] = temp[42];
  this->cube_string[39] = temp[41];
  this->cube_string[41] = temp[39];
  this->cube_string[42] = temp[38];
  this->cube_string[43] = temp[37];
  this->cube_string[44] = temp[36];

  setMirror();
}