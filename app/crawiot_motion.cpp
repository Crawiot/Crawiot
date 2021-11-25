#include "crawiot_motion.h"
#include "crawiot_location.h"
#include <Arduino.h>

Motion MotionModule;

static const int SERVO_MOVE_PIN = 13;
static const int SERVO_ROTATE_PIN = 12;

void Motion::setup(const Config &config) {
    this->tracker.setup(config);

    this->firstSpeedDegree = config.firstSpeedDegree;
    this->servoMove.attach(SERVO_MOVE_PIN);
    this->servoRotate.attach(SERVO_ROTATE_PIN);
    this->stop();
    this->servoRotate.write(85);
    this->servoMove.write(90);
}

void Motion::task() {
    this->tracker.task();
}

void Motion::execute(MotionEngineCommand command) {
    switch (command) {
        case MoveForward:
            moveTo(this->firstSpeedDegree);
            break;
        case Stop:
            this->stop();
            break;
        case Right:
            this->rotateToRight();
            break;
        case Left:
            this->rotateToLeft();
            break;
    }
}

void Motion::moveTo(int degree) {
    if (this->currentDegree == degree) {
        return;
    }

    this->servoMove.write(degree);
    this->currentDegree = degree;
}

void Motion::stop() {
    this->servoMove.write(90);
    this->currentDegree = 90;
}

void Motion::rotateToRight() {
    this->servoRotate.write(65);
    delay(300);
    servoMove.write(110);
    delay(500);
    servoMove.write(90);
    delay(300);
    this->servoRotate.write(105);
    delay(300);
    servoMove.write(70);
    delay(500);
    this->servoRotate.write(85);
    servoMove.write(90);
    delay(300);
}

void Motion::rotateToLeft() {
    this->servoRotate.write(105);
    delay(300);
    servoMove.write(110);
    delay(500);
    servoMove.write(90);
    delay(300);
    this->servoRotate.write(65);
    delay(300);
    servoMove.write(70);
    delay(500);
    this->servoRotate.write(85);
    servoMove.write(90);
    delay(300);
}

