#include "crawiot_motion_api.h"

void MotionApi::setup(const Config &config, const Servo &servoMove, const Servo &servoRotate) {
    if (config.enableMotionApi) {
        this->servoMove = servoMove;
        this->servoRotate = servoRotate;
    }
    this->enable = config.enableMotionApi;
}

bool MotionApi::move(int units) {
    if (!this->enable) {
        return false;
    }

    servoMove.write(units);
    return true;
}

bool MotionApi::rotate(int units) {
    if (!this->enable) {
        return false;
    }

    servoRotate.write(units);
    return true;
}
