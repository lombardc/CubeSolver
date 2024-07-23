#include "LED_Array.h"
#include "Cube_Lights.h"
#include <AccelStepper.h>
#include <StringSplitter.h>

#define STEPS 800

AccelStepper blanc(AccelStepper::DRIVER, 2, 52);
AccelStepper orange(AccelStepper::DRIVER, 3, 50);
AccelStepper jaune(AccelStepper::DRIVER, 4, 48);
AccelStepper vert(AccelStepper::DRIVER, 5, 46);
AccelStepper bleu(AccelStepper::DRIVER, 6, 44);
AccelStepper rouge(AccelStepper::DRIVER, 7, 42);


float MOTOR_SPEED = 500.0; //4000 // good lub, 5500
float MOTOR_ACC = 100000;//200000.0;
String OP_CODE;

const int LED_PINS[] = {28, 31, 29, 30, 40};
const int LED_MAPPINGS[][8] = {
    {2, 5, 8, 7, 6, 3, 0, 1},  // Blue
    {6, 3, 0, 1, 2, 5, 8, 7},  // Green
    {2, 1, 0, 3, 6, 7, 8, 5},  // Red
    {8, 5, 2, 1, 0, 3, 6, 7},  // Orange
    {8, 7, 6, 3, 0, 1, 2, 5}   // Yellow
};

LED_Array led_arrays[5] = {
    LED_Array(LED_PINS[0], LED_MAPPINGS[0]),
    LED_Array(LED_PINS[1], LED_MAPPINGS[1]),
    LED_Array(LED_PINS[2], LED_MAPPINGS[2]),
    LED_Array(LED_PINS[3], LED_MAPPINGS[3]),
    LED_Array(LED_PINS[4], LED_MAPPINGS[4])
};

Cube_Lights cube_lights(led_arrays[0], led_arrays[1], led_arrays[2], led_arrays[3], led_arrays[4]);


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

    cube_lights.setColor(255, 255, 255);
    cube_lights.setBrightness(50);
    Serial3.begin(115200);
}


void leds_power(String OPCODE) {
  cube_lights.setBrightness(OPCODE.toInt());
}

void lights(String OPCODE) {
    if (OPCODE == "RECO")
    {
      cube_lights.setColor(255, 255, 255);
    }
    else if (OPCODE == "SOLV")
    {
      cube_lights.resetCubeString();
      cube_lights.setMirror();
    }
    else if (OPCODE == "FLAS")
    {
      cube_lights.setColor(0, 0, 255);
    }
        else if (OPCODE == "CALI")
    {
      cube_lights.setColor(255, 0, 0);
    }
}

void sequence(String OPCODE, bool led_show) {
  StringSplitter *splitter = new StringSplitter(OPCODE, '-', 50);
  int itemCount = splitter->getItemCount();
  
  for (int i = 0; i < itemCount; i++) {
    String item = splitter->getItemAtIndex(i);
    moveAxles(item, led_show);
  }

  delete splitter;
  splitter = NULL;
}

void moveAxles(String OPCODE, bool led_show) {
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

    StringSplitter *splitter1 = new StringSplitter(OPCODE, ':', 2);
    int itemCount = splitter1->getItemCount();

    AccelStepper motors_to_move[2] = {};

    for (int i = 0; i < itemCount; i++) {
      String item = splitter1->getItemAtIndex(i);
      for (const auto& move : moves) {
        if (item == move.face) {
            move.motor.enableOutputs();
            move.motor.moveTo(move.motor.currentPosition() + STEPS / 4);
            motors_to_move[i] = move.motor;
        }
        else if (item == move.face + "'") {
            move.motor.enableOutputs();
            move.motor.moveTo(move.motor.currentPosition() - STEPS / 4);
            motors_to_move[i] = move.motor;
        }
        else if (item == move.face + "2") {
            move.motor.enableOutputs();
            move.motor.moveTo(move.motor.currentPosition() + STEPS / 2);
            motors_to_move[i] = move.motor;
        }
      }
      if (led_show) {
      cube_lights.rotate(item);
    }
    }

    while(motors_to_move[0].distanceToGo() != 0 or motors_to_move[1].distanceToGo() != 0){
      if (motors_to_move[0].distanceToGo() != 0){motors_to_move[0].run();}
      if (motors_to_move[1].distanceToGo() != 0){motors_to_move[1].run();}
    }

    motors_to_move[0].disableOutputs();
    motors_to_move[1].disableOutputs();

  delete splitter1;
  splitter1 = NULL;
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
  else if (OP_CODE.substring(0, 4) == "QUIC"){
      sequence(OP_CODE.substring(5), false);
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
      cube_lights.setCubeString(OP_CODE.substring(5));
      cube_lights.setMirror();
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