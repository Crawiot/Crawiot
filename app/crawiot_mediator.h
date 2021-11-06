#ifndef APP_CRAWIOT_MEDIATOR_H
#define APP_CRAWIOT_MEDIATOR_H

#include "crawiot_location.h"
#include <freertos/FreeRTOS.h>
#include "freertos/queue.h"

struct SubtargetsContainer {
    const Coordinates* subtargets;
    size_t size;
};

class Mediator {
public:
    void setup();

    bool push_subtargets(const SubtargetsContainer &);

    bool pull_subtargets(SubtargetsContainer *);

    bool push_sub_target(const Coordinates &);

    bool pull_sub_target(Coordinates *);

private:
    xQueueHandle subtargets_lists_queue;
    xQueueHandle sub_targets_queue;
};

extern Mediator ModulesMediator;

#endif //APP_CRAWIOT_MEDIATOR_H
