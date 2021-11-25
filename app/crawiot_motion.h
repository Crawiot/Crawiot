#ifndef APP_CRAWIOT_MOTION_H
#define APP_CRAWIOT_MOTION_H

#include <Servo.h>
#include "crawiot_config.h"
#include "crawiot_motion_tracker.h"
#include "crawiot_motion_api.h"

enum MotionEngineCommand {
    Stop,
    MoveForward,
    Right,
    Left,
};

class Motion {
public:
    void setup(const Config&);
    void executeEngineCommand(MotionEngineCommand);
    void task();

    MotionApi motionApi;
private:
    Servo servoMove;
    Servo servoRotate;
    int firstSpeedDegree;
    Tracker tracker;
    void moveTo(int degree);
    int currentDegree;
    void stop();

    void rotateToRight();


    void rotateToLeft();
};

extern Motion MotionModule;

#endif //APP_CRAWIOT_MOTION_H
