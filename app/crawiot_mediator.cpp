#include "crawiot_mediator.h"

Mediator ModulesMediator = Mediator();

void Mediator::setup() {
    this->sub_targets_queue = xQueueCreate(3, sizeof(Coordinates));
    this->subtargets_lists_queue = xQueueCreate(3, sizeof(SubtargetsContainer));
}

bool Mediator::pushSubTarget(const Coordinates &coordinates) {
    return xQueueSend(
                   this->sub_targets_queue,
                   &coordinates,
                   pdMS_TO_TICKS(1000)
           ) == pdPASS;
}

bool Mediator::pullSubTarget(Coordinates *coordinates) {
    return xQueueReceive(this->sub_targets_queue, coordinates, 0) == pdTRUE;
}

bool Mediator::pushSubtargets(const SubtargetsContainer &subtargetsContainer) {
    return xQueueSend(this->subtargets_lists_queue, &subtargetsContainer, 0) == pdPASS;
}

bool Mediator::pullSubtargets(SubtargetsContainer *subtargetsContainer) {
    return xQueueReceive(this->subtargets_lists_queue, subtargetsContainer, 0) == pdTRUE;
}
