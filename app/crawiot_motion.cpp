#include "crawiot_motion.h"
#include <Arduino.h>

extern Motion MotionModule;

static const int SERVO_PIN_D13 = 13;

void Motion::setup(const Config &config) {
    this->firstSpeedDegree = config.FirstSpeedDegree;
    this->servo.attach(SERVO_PIN_D13);
}

void Motion::startRotate(int degree) {
    for (int posDegrees = 0; posDegrees <= degree; posDegrees++) {
        this->servo.write(posDegrees);
        delay(40); //Скорость вращения если что поменяем тут
    }
}

void Motion::stopRotate() {
    this->servo.write(0);
}

void Motion::execute(MotionEngineCommand command) {
    switch (command) {
        case MoveForward:
            startRotate(this->firstSpeedDegree);
            break;
        case Stop:
            stopRotate();
            break;
    }
}
