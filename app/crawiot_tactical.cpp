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
        if (!this->hasCurrentTarget) {
            was_pulled = ModulesMediator.pullSubTarget(&this->currentTarget);
            this->hasCurrentTarget = was_pulled;
        }

        this->reach_current_target();

        if (!this->hasCurrentTarget && !this->needStop){
            vTaskDelay(pdMS_TO_TICKS(500));
        }
    }
}

void Tactical::reach_current_target() {
    if (!this->hasCurrentTarget) {
        //if (this->needStop)
        {
            GlobalTracer.sendTrace("Tactical. Stop");
            MotionModule.execute(Stop);
            this->needStop = false;
        }
        return;
    }
    
    String message = "Tactical. Reaching ";
    message.concat(this->currentTarget.X);
    message.concat(", ");
    message.concat(this->currentTarget.Y);
    GlobalTracer.sendTrace(message);
    
    const float diff = calculateDiff(GlobalLocationManager.currentLocation.X, this->currentTarget.X);
    if (diff > 0) {
        GlobalTracer.sendTrace("Tactical. Moving forward");
        MotionModule.execute(MoveForward);
        vTaskDelay(pdMS_TO_TICKS(100));
    } else {
        this->hasCurrentTarget = false;
        this->needStop = true;
    }
}