#ifndef APP_CRAWIOT_MOTION_H
#define APP_CRAWIOT_MOTION_H

#include <Servo.h>
#include "crawiot_config.h"

enum MotionEngineCommand {
    Stop,
    MoveForward,
};

class Motion {
public:
    void setup(const Config&);
    void execute(MotionEngineCommand);

private:
    Servo servo;
    int firstSpeedDegree;

    int wheelRadius;

    void startRotate(int degree);

    void onWheelRotation();
};

extern Motion MotionModule;

#endif //APP_CRAWIOT_MOTION_H
