#include "crawiot_traces.h"
#include "crawiot_mediator.h"
#include "crawiot_strategic.h"
#include "crawiot_common.h"
#include <freertos/task.h>
#include <cmath>

[[noreturn]] void Strategic::task() {
    while (1) {

        SubtargetsContainer container;
        const bool wasPulled = ModulesMediator.pullSubtargets(&container);

        if (wasPulled) {
            GlobalTracer.sendTrace("Strategic. Target acquired");
            this->processSubtargets(container);
        }

        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

void Strategic::processSubtargets(const SubtargetsContainer container) {
    const float currentX = GlobalLocationManager.currentLocation.X;
    const float firstX = container.subtargets[0].X;

    const float diff = calculateDiff(currentX, firstX);
    if (diff < 0) {
        String message = "Strategic. Can't reach the target: ";
        message.concat(firstX);
        message.concat(". Current X: ");
        message.concat(currentX);
        GlobalTracer.sendTrace(message);
        return;
    }

    for (size_t index = 0; index < container.size;) {
        const bool wasPushed = ModulesMediator.pushSubTarget(container.subtargets[index]);
        if (wasPushed) {
            index += 1;
        }
    }

    delete[] container.subtargets;
    GlobalTracer.sendTrace("Strategic. All sub targets were pushed");
}