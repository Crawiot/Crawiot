#include "crawiot_strategic.h"
#include "crawiot_traces.h"
#include "crawiot_mediator.h"

Strategic StrategicModule = Strategic();

[[noreturn]] void Strategic::task(void *pvParameters) {
    while (1) {
        GlobalTracer.send_trace("Strategic module is running");

        Coordinates target;
        const bool was_pulled = ModulesMediator.pull_target(&target);
        GlobalTracer.send_trace(was_pulled ? "Strategic. Target pulled" : "Strategic. No target");

        if (was_pulled) {
            StrategicModule.reach_coordinates(target);
        }

        delay(1000);
    }
}

void Strategic::reach_coordinates(const Coordinates coordinates) {
    for (int i = 0; i < coordinates.X; ++i) {
        
        const Coordinates sub_crods = {
                .X = static_cast<float>(i),
                .Y = coordinates.Y
        };
        
        ModulesMediator.push_sub_target(sub_crods);
    }
}