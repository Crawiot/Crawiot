#ifndef APP_CRAWIOT_MEDIATOR_H
#define APP_CRAWIOT_MEDIATOR_H

#include "common.h"

class Mediator {
public:
    void push_coordinates(const Coordinates);
    Coordinates pull_coordinates();
};

extern Mediator ModulesMediator;

#endif //APP_CRAWIOT_MEDIATOR_H
