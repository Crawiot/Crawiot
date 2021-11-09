#include "crawiot_motion.h"
#include "crawiot_location.h"
#include <Arduino.h>

Motion MotionModule;

static const int SERVO_MOVE = 13;
static const int SERVO_ROTATE = 12;

void Motion::setup(const Config &config) {
    this->tracker.setup(config);
    
    this->firstSpeedDegree = config.firstSpeedDegree;
    this->servo_move.attach(SERVO_MOVE);
    this->servo_rotate.attach(SERVO_ROTATE);
    this->stopRotate();
    
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
            this->stopRotate();
            break;
        case Right:
            this->RotateThirteenToRight();
            break;
        case Left:
            this->RotateFifteenToLeft();
            break;
    }
}

void Motion::startRotate(int degree) {
    if (this->currentDegree == degree){
        return;
    }
    
    this->servo.write(degree);
    this->currentDegree = degree;
}

void Motion::stopRotate(){
    this->servo.write(90);
    this->currentDegree = 90;
}

void Motion::RotateThirteenToRight() {
    for (int i = 0; i < 2; i++) {
        servo_rotate.write(65);
        delay(300);
        servo_move.write(110);
        delay(500);
        servo_move.write(90);
        delay(300);
        servo_rotate.write(105);
        delay(300);
        servo_move.write(70);
        delay(500);
        servo_rotate.write(85);
        servo_move.write(90);
        delay(300);
    }
}

void Motion::RotateFifteenToLeft() {
    for (int i = 0; i < 2; i++) {
        servo_rotate.write(105);
        delay(300);
        servo_move.write(110);
        delay(500);
        servo_move.write(90);
        delay(300);
        servo_rotate.write(65);
        delay(300);
        servo_move.write(70);
        delay(500);
        servo_rotate.write(85);
        servo_move.write(90);
        delay(300);
    }
}

