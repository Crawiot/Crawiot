#ifndef APP_CRAWIOT_MOTION_H
#define APP_CRAWIOT_MOTION_H

#include <Servo.h>
#include "crawiot_config.h"
#include "crawiot_motion_tracker.h"

enum MotionEngineCommand {
    Stop,
    MoveForward,
};

class Motion {
public:
    void setup(const Config&);
    void execute(MotionEngineCommand);
    void task();
private:
    Servo servo;
    int firstSpeedDegree;
    Tracker tracker;
    void startRotate(int degree);
};

extern Motion MotionModule;

#endif //APP_CRAWIOT_MOTION_H
