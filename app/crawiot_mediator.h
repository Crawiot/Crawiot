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

    bool pushSubtargets(const SubtargetsContainer &);

    bool pullSubtargets(SubtargetsContainer *);

    bool pushSubTarget(const Coordinates &);

    bool pullSubTarget(Coordinates *);

private:
    xQueueHandle subtargetsContainerQueue;
    xQueueHandle subTargetsQueue;
};

extern Mediator ModulesMediator;

#endif //APP_CRAWIOT_MEDIATOR_H
