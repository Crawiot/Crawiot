#include "crawiot_tactical.h"
#include "Arduino.h"
#include "crawiot_traces.h"
#include "crawiot_mediator.h"
#include "crawiot_motion.h"

Tactical TacticalModule = Tactical();

[[noreturn]] void Tactical::task(void *pvParameters) {
    while (1) {
        Coordinates cords;

        bool was_pulled = true;
        if (!TacticalModule.has_current_target) {
            was_pulled = ModulesMediator.pull_sub_target(&cords);

            if (was_pulled) {
                TacticalModule.current_target = cords;
                TacticalModule.has_current_target = true;
            }
        }
        TacticalModule.reach_target(cords,was_pulled);
        delay(500);
    }
}

void Tactical::reach_target(const Coordinates &target_coordinates, bool was_pulled) {
    if (!TacticalModule.has_current_target){
        if (!was_pulled)
            MotionModule.execute(Stop);
        return;
    }

        if (GlobalLocationManager.current_location.X - this->current_target.X < 0) {
            MotionModule.execute(MoveForward);
        }
        else {
            this->has_current_target = false;
        }

}