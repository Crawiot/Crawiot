#include "crawiot_mediator.h"

Mediator ModulesMediator = Mediator();

void Mediator::setup() {
    this->subTargetsQueue = xQueueCreate(3, sizeof(Coordinates));
    this->subtargetsContainerQueue = xQueueCreate(3, sizeof(SubtargetsContainer));
}

bool Mediator::pushSubTarget(const Coordinates &coordinates) {
    return xQueueSend(
                   this->subTargetsQueue,
                   &coordinates,
                   pdMS_TO_TICKS(1000)
           ) == pdPASS;
}

bool Mediator::pullSubTarget(Coordinates *coordinates) {
    return xQueueReceive(this->subTargetsQueue, coordinates, 0) == pdTRUE;
}

bool Mediator::pushSubtargets(const SubtargetsContainer &subtargetsContainer) {
    return xQueueSend(this->subtargetsContainerQueue, &subtargetsContainer, 0) == pdPASS;
}

bool Mediator::pullSubtargets(SubtargetsContainer *subtargetsContainer) {
    return xQueueReceive(this->subtargetsContainerQueue, subtargetsContainer, 0) == pdTRUE;
}
