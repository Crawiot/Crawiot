#ifndef APP_CRAWIOT_STRATEGIC_H
#define APP_CRAWIOT_STRATEGIC_H

#include "crawiot_location.h"

class Strategic {
public:
    [[noreturn]] void task();
private:
    void reach_coordinates(const Coordinates);
};

extern Strategic StrategicModule;

int calculate_diff(int current, int target) {
    return target - current;
}

#endif //APP_CRAWIOT_STRATEGIC_H
