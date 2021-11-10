#ifndef APP_CRAWIOT_TACTICAL_H
#define APP_CRAWIOT_TACTICAL_H

#include "crawiot_location.h"

class Tactical {
public:
    [[noreturn]] void task();
private:
    void reach_current_target();
    Coordinates currentTarget;
    bool hasCurrentTarget;
    bool needStop;

    void makeRotation();
};

#endif //APP_CRAWIOT_TACTICAL_H
