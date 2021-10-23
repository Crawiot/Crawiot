#ifndef APP_CRAWIOT_MOTION_TRACKER_H
#define APP_CRAWIOT_MOTION_TRACKER_H

#include <freertos/FreeRTOS.h>
#include <freertos/queue.h>
#include "crawiot_config.h"

class Tracker {
public:
    void setup(const Config&);

    [[noreturn]] void task();
};

#endif //APP_CRAWIOT_MOTION_TRACKER_H
