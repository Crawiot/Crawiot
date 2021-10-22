#ifndef APP_CRAWIOT_TACTICAL_H
#define APP_CRAWIOT_TACTICAL_H

#include "crawiot_location.h"

class Tactical {
public:
    [[noreturn]] void task();
private:
    void reach_current_target();
    Coordinates current_target;
    bool has_current_target;
};

#endif //APP_CRAWIOT_TACTICAL_H
