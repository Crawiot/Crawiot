#include "crawiot_tactical.h"
#include "crawiot_mediator.h"
#include "crawiot_motion.h"
#include "crawiot_traces.h"
#include "crawiot_common.h"
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

[[noreturn]] void Tactical::task() {
    while (1) {
        
        bool was_pulled;
        if (!this->has_current_target) {
            was_pulled = ModulesMediator.pull_sub_target(&this->current_target);
            this->has_current_target = was_pulled;
        }

        this->reach_current_target();

        if (!this->has_current_target && !this->need_stop){
            vTaskDelay(pdMS_TO_TICKS(500));
        }
    }
}

void Tactical::reach_current_target() {
    if (!this->has_current_target) {
        if (this->need_stop) {
            GlobalTracer.send_trace("Tactical. Stop");
            MotionModule.execute(Stop);
            this->need_stop = false;
        }
        return;
    }

    const int diff = calculate_diff(this->current_target.X, GlobalLocationManager.current_location.X);
    if (diff > 0) {
        GlobalTracer.send_trace("Tactical. Moving forward");
        MotionModule.execute(MoveForward);
    } else {
        this->has_current_target = false;
        this->need_stop = true;
    }
}