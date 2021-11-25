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

        if (this->hasCurrentTarget) {
            this->makeRotation();
            this->reach_current_target();
        } else {
            vTaskDelay(pdMS_TO_TICKS(500));
        }
    }
}


void Tactical::makeRotation() {
    GlobalTracer.sendTrace("Tactical. makeRotation");
    const auto currentY = GlobalLocationManager.currentLocation.Y;
    const auto targetY = this->currentTarget.Y;
    const float diffY = calculateDiff(currentY, targetY);

    const auto currentX = GlobalLocationManager.currentLocation.X;
    const auto targetX = this->currentTarget.X;
    const float diffX = calculateDiff(currentX, targetX);

    const float currentAngle = GlobalLocationManager.currentAngle;
    float targetAngle;

    if (diffX == 0 && diffY == 0) {
        targetAngle = currentAngle;
    } else if (diffX == 0) {
        targetAngle = (diffY > 0) ? M_PI / 2 : -1 * M_PI / 2;
    } else if (diffY == 0) {
        targetAngle = diffX > 0 ? 0 : M_PI;
    } else if (diffX > 0) {
        targetAngle = (diffY > 0) ? atan(diffY / diffX) : -1 * atan(diffY / diffX);
    } else {
        targetAngle = (diffY > 0) ? M_PI - atan(diffY / diffX) : -1 * M_PI + atan(diffY / diffX);
    }

    String angleMsg = "Tactical. TargetAngle ";
    angleMsg.concat(targetAngle);
    GlobalTracer.sendTrace(angleMsg);
    
    if (targetAngle != currentAngle) {
        const auto direction = targetAngle > currentAngle ? Left : Right;
        
        const auto angleDiff = abs(targetAngle - currentAngle);
        auto commandsToExecuteCount = direction == Left 
                ? ceil(angleDiff / 0.2261)
                : floor(angleDiff / 0.2261);

        GlobalLocationManager.disableUpdates = true;
        MotionModule.execute(Stop);

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

    int counter = 0;
    while (counter < pathLength) {
        MotionModule.execute(MoveForward);
        vTaskDelay(pdMS_TO_TICKS(500));
        counter++;

        const auto cos_val = cos(GlobalLocationManager.currentAngle);
        const auto sin_val = sin(GlobalLocationManager.currentAngle);
        GlobalLocationManager.currentLocation.X += cos_val;
        GlobalLocationManager.currentLocation.Y += sin_val;
        GlobalLocationManager.currentSegmentPosition += 1;

        String message = "Motion. Current coordinate ";
        message.concat(GlobalLocationManager.currentLocation.X);
        message.concat(", ");
        message.concat(GlobalLocationManager.currentLocation.Y);
        GlobalTracer.sendTrace(message);
    }
    MotionModule.execute(Stop);

    this->hasCurrentTarget = false;
    this->needStop = true;

    message = "Tactical. Stop at ";
    message.concat(this->currentTarget.X);
    message.concat(", ");
    message.concat(this->currentTarget.Y);
    GlobalTracer.sendTrace(message);
}