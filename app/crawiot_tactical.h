#ifndef APP_CRAWIOT_TACTICAL_H
#define APP_CRAWIOT_TACTICAL_H

#include "crawiot_location.h"

class Tactical {
public:
    static void task(void *pvParameters);

    void reach_target(const Coordinates[], int count);
};

extern Tactical TacticalModule;

#endif //APP_CRAWIOT_TACTICAL_H
