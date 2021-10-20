//
// Created by user on 10/10/2021.
//

#include "crawiot_motion.h"
#include <Servo.h>

static const int servoPin = 13;
static const int degree = 90; //Для начала какой-нить рандомный угол поворота
Servo servo1;

void setup() {
    Serial.begin(115200);
    servo1.attach(servoPin);
}
void startRotate(int degree){
  for(int posDegrees = 0; posDegrees <= degree; posDegrees++) {
        servo1.write(posDegrees);
        delay(40); //Скорость вращения если что поменяем тут
    }
}

void stopRotate(int degree){
  for(int posDegrees = degree; posDegrees >= 0; posDegrees--) {
        servo1.write(posDegrees);
        delay(40);
    }
}



void loop() { //Она пока будет крутиться до конца, немного ждать и топать обратно
  startRotate(degree);
  delay(1000);
  stopRotate(degree);
  
}
