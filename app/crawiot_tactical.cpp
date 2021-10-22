#include "crawiot_tactical.h"
#include "crawiot_mediator.h"
#include "crawiot_motion.h"
#include "crawiot_strategic.h"
#include "crawiot_traces.h"

[[noreturn]] void Tactical::task() {
    while (1) {
        if (!this->has_current_target) {
            const bool was_pulled = ModulesMediator.pull_sub_target(&this->current_target);
            this->has_current_target = was_pulled;
        }

        this->reach_current_target();
    }
}

void Tactical::reach_current_target() {
    if (!this->has_current_target) {
        GlobalTracer.send_trace("Tactical. Stop");
        MotionModule.execute(Stop);
        return;
    }

    const int diff = calculate_diff(this->current_target.X, GlobalLocationManager.current_location.X);
    if (diff > 0) {
        GlobalTracer.send_trace("Tactical. Moving forward");
        MotionModule.execute(MoveForward);
    } else {
        this->has_current_target = false;
    }
}