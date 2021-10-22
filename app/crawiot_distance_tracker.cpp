#include "crawiot_distance_tracker.h"
#include <Arduino.h>
#include Math;

static const int HALL_PIN_D13 = 32;

void Motion::setup(const Config &config) {
    this->wheelRadius = config.WheelRadius;
    this->servo.attach(SERVO_PIN_D13);
    pinMode(HALL_PIN_D13, INPUT);
    attachInterrupt(PIN, calculate, FALLING);
}

void Motion::stopRotate() {
    this->servo.write(0);
}
void IRAM_ATTR calculate() {
  GlobalLocationManager.current_location.X += (int) 2 * 3.1415 * this->wheelRadius;
}
