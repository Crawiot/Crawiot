#include "crawiot_motion.h"
#include "crawiot_location.h"
#include <Arduino.h>

Motion MotionModule;

static const int SERVO_PIN_D13 = 13;

void Motion::setup(const Config &config) {
    this->tracker.setup(config);
    
    this->firstSpeedDegree = config.firstSpeedDegree;
    this->servo.attach(SERVO_PIN_D13);
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