#include "crawiot_mediator.h"

Mediator ModulesMediator = Mediator();

void Mediator::setup() {
    this->sub_targets_queue = xQueueCreate(3, sizeof(Coordinates));
    this->subtargets_lists_queue = xQueueCreate(3, sizeof(SubtargetsContainer));
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

bool Mediator::push_subtargets(const SubtargetsContainer &subtargetsContainer) {
    return xQueueSend(this->subtargets_lists_queue, &subtargetsContainer, 0) == pdPASS;
}

bool Mediator::pull_subtargets(SubtargetsContainer *subtargetsContainer) {
    return xQueueReceive(this->subtargets_lists_queue, subtargetsContainer, 0) == pdTRUE;
}
