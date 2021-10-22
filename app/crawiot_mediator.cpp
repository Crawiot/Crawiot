#include "crawiot_mediator.h"

Mediator ModulesMediator = Mediator();

void Mediator::setup() {
    this->sub_targets_queue = xQueueCreate(10, sizeof(Coordinates));
    this->targets_queue = xQueueCreate(3, sizeof(Coordinates));
}

bool Mediator::push_target(const Coordinates &coordinates) {
    return xQueueSend(this->targets_queue, &coordinates, 0) == pdPASS;
}

bool Mediator::pull_target(Coordinates *coordinates) {
    return xQueueReceive(this->targets_queue, coordinates, 0) == pdTRUE;
}

bool Mediator::push_sub_target(const Coordinates &coordinates) {
    return xQueueSend(
                   this->sub_targets_queue,
                   &coordinates,
                   pdMS_TO_TICKS(1000)
           ) == pdPASS;
}

bool Mediator::pull_sub_target(Coordinates *coordinates) {
    return xQueueReceive(this->sub_targets_queue, coordinates, 0) == pdTRUE;
}