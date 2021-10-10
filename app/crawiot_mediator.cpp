#include "crawiot_mediator.h"
#include "crawiot_traces.h"

Mediator ModulesMediator = Mediator();

void Mediator::push_coordinates(const Coordinates coordinates) {
    GlobalTracer.send_trace("Coordinates pushed");
}

Coordinates Mediator::pull_coordinates() {
    struct Coordinates cords = {
            .X = 0.32,
            .Y = 3.1
    };
    GlobalTracer.send_trace("Coordinates pulled");
    return cords;
}
