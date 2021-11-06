#include "crawiot_traces.h"
#include "crawiot_mediator.h"
#include "crawiot_strategic.h"
#include "crawiot_common.h"
#include <freertos/task.h>
#include <cmath>

[[noreturn]] void Strategic::task() {
    while (1) {

        SubtargetsContainer container;
        const bool was_pulled = ModulesMediator.pull_subtargets(&container);

        if (was_pulled) {
            GlobalTracer.send_trace("Strategic. Target acquired");
            this->process_subtargets(container);
        }

        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

void Strategic::process_subtargets(const SubtargetsContainer container) {
    const float current_x = GlobalLocationManager.current_location.X;
    const float first_x = container.subtargets[0].X;

    const float diff = calculate_diff(current_x, first_x);
    if (diff < 0) {
        String message = "Strategic. Can't reach the target: ";
        message.concat(first_x);
        message.concat(". Current X: ");
        message.concat(current_x);
        GlobalTracer.send_trace(message);
        return;
    }

    for (size_t index = 0; index < container.size;) {
        const bool was_pushed = ModulesMediator.push_sub_target(container.subtargets[index]);
        if (was_pushed) {
            index += 1;
        }
    }

    delete[] container.subtargets;
    GlobalTracer.send_trace("Strategic. All sub targets were pushed");
}