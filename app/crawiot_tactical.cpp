#include "crawiot_tactical.h"
#include "crawiot_mediator.h"
#include "crawiot_motion.h"
#include "crawiot_traces.h"
#include "crawiot_common.h"
#include "math.h"
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

[[noreturn]] void Tactical::task() {
    while (1) {

        bool wasPulled;
        if (!this->hasCurrentTarget) {
            wasPulled = ModulesMediator.pullSubTarget(&this->currentTarget);
            this->hasCurrentTarget = wasPulled;
        }

        this->makeRotation();
        this->reach_current_target();

        if (!this->hasCurrentTarget && !this->needStop) {
            vTaskDelay(pdMS_TO_TICKS(500));
        }
    }
}


void Tactical::makeRotation() {
    const auto currentY = GlobalLocationManager.currentLocation.Y;
    const auto targetY = this->currentTarget.Y;
    const float diffY = calculateDiff(currentY, targetY);

    const auto currentX = GlobalLocationManager.currentLocation.X;
    const auto targetX = this->currentTarget.X;
    const float diffX = calculateDiff(currentX, targetX);

    const float currentAngle = GlobalLocationManager.currentAngle;
    const float targetAngle;

    if(diffX == 0) {
        targetAngle = (diffY > 0) ? M_PI/2 : -1 * M_PI/2;
    } else if(diffY == 0) {
        targetAngle = diffX > 0 ? 0 : M_PI;
    } else if(diffX > 0) {
        targetAngle = (diffY > 0) ? atan(diffY / diffX) : -1 * atan(diffY / diffX);
    } else {
        targetAngle = (diffY > 0) ? M_PI - atan(diffY / diffX) : -1 * M_PI + atan(diffY / diffX);
    }
    targetAngle = targetAngle * 180 / M_PI; //Radian to degree
    }

    if (targetAngle != currentAngle) {
        const auto angleDiff = abs(targetAngle - currentAngle);
        auto commandsToExecuteCount = ceil(angleDiff / 13);

        GlobalLocationManager.disableUpdates = true;
        MotionModule.execute(Stop);

        const auto direction = targetAngle > currentAngle ? Left : Right;
        for (int i = 0; i < commandsToExecuteCount; i++) {
            MotionModule.execute(direction);
        }
        GlobalLocationManager.disableUpdates = false;
        GlobalLocationManager.currentAngle = targetAngle;
    }
}

void Tactical::reach_current_target() {
    String message = "Tactical. Reaching ";
    message.concat(this->currentTarget.X);
    message.concat(", ");
    message.concat(this->currentTarget.Y);
    GlobalTracer.sendTrace(message);

    float startPosition = GlobalLocationManager.currentSegmentPosition;
    float x_0 = GlobalLocationManager.currentLocation.X;
    float y_0 = GlobalLocationManager.currentLocation.Y;
    float x_1 = this->currentTarget.X;
    float y_1 = this->currentTarget.Y;
    float pathLength = sqrt((x_1 - x_0) * (x_1 - x_0) + (y_1 - y_0) * (y_1 - y_0));

    float diff = GlobalLocationManager.currentSegmentPosition - startPosition;
    while (diff < pathLength) {
        MotionModule.execute(MoveForward);
        vTaskDelay(pdMS_TO_TICKS(100));
        diff = GlobalLocationManager.currentSegmentPosition - startPosition;
    }
    MotionModule.execute(Stop);

    String message = "Tactical. Stop at ";
    message.concat(this->currentTarget.X);
    message.concat(", ");
    message.concat(this->currentTarget.Y);
    GlobalTracer.sendTrace(message);
}