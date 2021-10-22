#include "crawiot_motion.h"
#include "crawiot_location.h"
#include <Arduino.h>

Motion MotionModule;

static const int SERVO_PIN_D13 = 13;

void Motion::setup(const Config &config) {
    this->tracker.setup(config);
    
    this->firstSpeedDegree = config.FirstSpeedDegree;
    this->servo.attach(SERVO_PIN_D13);
}

void Motion::task() {
    this->tracker.task();
}

void Motion::execute(MotionEngineCommand command) {
    switch (command) {
        case MoveForward:
            startRotate(this->firstSpeedDegree);
            break;
        case Stop:
            this->servo.write(0);
            break;
    }
}

void Motion::startRotate(int degree) {
    for (int posDegrees = 0; posDegrees <= degree; posDegrees++) {
        this->servo.write(posDegrees);
        delay(40); //Скорость вращения если что поменяем тут
    }
}