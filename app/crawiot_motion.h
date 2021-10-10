#ifndef APP_CRAWIOT_MOTION_H
#define APP_CRAWIOT_MOTION_H

enum MotionEngineCommand {
    Stop,
    MoveForward,
};

class Motion {
public:
    void setup();
    void execute(MotionEngineCommand);
};

extern Motion MotionModule;

#endif //APP_CRAWIOT_MOTION_H
