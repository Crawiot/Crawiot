#ifndef APP_CRAWIOT_MEDIATOR_H
#define APP_CRAWIOT_MEDIATOR_H

#include "crawiot_location.h"
#include <freertos/FreeRTOS.h>
#include "freertos/queue.h"

class Mediator {
public:
    void setup();

    bool push_target(const Coordinates&);

    bool pull_target(Coordinates*);

    bool push_sub_target(const Coordinates&);

    bool pull_sub_target(Coordinates*);

private:
    xQueueHandle targets_queue;
    xQueueHandle sub_targets_queue;
};

extern Mediator ModulesMediator;

#endif //APP_CRAWIOT_MEDIATOR_H
