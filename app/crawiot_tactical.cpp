#include "crawiot_tactical.h"
#include "Arduino.h"
#include "crawiot_traces.h"
#include "crawiot_mediator.h"

Tactical TacticalModule = Tactical();

[[noreturn]] void Tactical::task(void *pvParameters) {
    while (1) {
        Coordinates cords;
        
        const bool was_pulled = ModulesMediator.pull_sub_target(&cords);
        if (was_pulled) {
            TacticalModule.reach_target(cords);
        }
        
        delay(500);
    }
}

void Tactical::reach_target(const Coordinates &target_coordinates) {
    String empty = "TacticalModule. Reaching: ";
    empty.concat(target_coordinates.X);
    GlobalTracer.send_trace(empty);
}