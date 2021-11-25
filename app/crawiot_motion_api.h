#ifndef APP_CRAWIOT_MOTION_API_H
#define APP_CRAWIOT_MOTION_API_H

#include <Servo.h>
#include "crawiot_config.h"

class MotionApi {
public:
    void setup(const Config& config, const Servo& servoMove, const Servo& servoRotate);
    
    bool move(int units);
    bool rotate(int units);

private:
    Servo servoMove;
    Servo servoRotate;
    bool enable;
};

#endif //APP_CRAWIOT_MOTION_API_H
