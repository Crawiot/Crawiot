#ifndef APP_CRAWIOT_DISTANCE_TRACKER_H
#define APP_CRAWIOT_DISTANCE_TRACKER_H

#include "crawiot_config.h"

class Tracker {
public:
    void setup(const Config&);
private:
    int wheelRadius;
    void incrementDistance();
};

#endif //APP_CRAWIOT_DISTANCE_TRACKER_H
