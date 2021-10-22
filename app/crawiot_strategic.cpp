#include "crawiot_strategic.h"
#include "crawiot_traces.h"
#include "crawiot_mediator.h"
#include <freertos/task.h>
#include <cmath>

[[noreturn]] void Strategic::task() {
    while (1) {

        Coordinates target;
        const bool was_pulled = ModulesMediator.pull_target(&target);

        if (was_pulled) {
            GlobalTracer.send_trace("Strategic. Target acquired");
            this->reach_coordinates(target);
        }

        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

void Strategic::reach_coordinates(const Coordinates coordinates) {
    const int current_x = GlobalLocationManager.current_location.X;

    float diff = calculate_diff(coordinates.X, current_x);

    if (diff < 0) {
        GlobalTracer.send_trace("Strategic. Can't reach the target");
        return;
    }

    for (int sub_target_x = current_x; calculate_diff(sub_target_x, coordinates.X) >= 1;) {
        const Coordinates sub_target = {
                .X = sub_target_x,
                .Y = GlobalLocationManager.current_location.Y
        };
        const bool was_pushed = ModulesMediator.push_sub_target(sub_target);
        
        if (was_pushed) {
            sub_target_x += 1;
        }
    }
    GlobalTracer.send_trace("Strategic. Diff is less than 1");
}