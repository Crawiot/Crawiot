#ifndef APP_CRAWIOT_TACTICAL_H
#define APP_CRAWIOT_TACTICAL_H

#include "crawiot_location.h"

class Tactical {
public:
    [[noreturn]] static void task(void *pvParameters);

    void reach_target(const Coordinates&);
};

extern Tactical TacticalModule;

#endif //APP_CRAWIOT_TACTICAL_H
