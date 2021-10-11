#ifndef APP_CRAWIOT_STRATEGIC_H
#define APP_CRAWIOT_STRATEGIC_H

#include "crawiot_location.h"

class Strategic {
public:
    static void task(void *pvParameters);

    void reach_target();
private:
    void reach_coordinates(const Coordinates);
};

extern Strategic StrategicModule;

#endif //APP_CRAWIOT_STRATEGIC_H
