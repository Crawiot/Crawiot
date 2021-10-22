#include "crawiot_motion.h"
#include "crawiot_location.h"
#include <Arduino.h>

Motion MotionModule;

static const int SERVO_PIN_D13 = 13;
static const int HALL_PIN_D4 = 4;

void Motion::setup(const Config &config) {
    this->wheelRadius = config.WheelRadius;
    pinMode(HALL_PIN_D4, INPUT);
    attachInterrupt(HALL_PIN_D4, []() {
        MotionModule.onWheelRotation();
    }, FALLING);

    this->firstSpeedDegree = config.FirstSpeedDegree;
    this->servo.attach(SERVO_PIN_D13);
}

void Motion::onWheelRotation() {
    const float val = (int) 2 * 3.1415 * this->wheelRadius;
    GlobalLocationManager.current_location.X += val;
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