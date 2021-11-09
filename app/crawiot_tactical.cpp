#include "crawiot_tactical.h"
#include "crawiot_mediator.h"
#include "crawiot_motion.h"
#include "crawiot_traces.h"
#include "crawiot_common.h"
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
    //Получаем новые Х и У
    const auto currentX = GlobalLocationManager.currentLocation.X;
    const auto currentY = GlobalLocationManager.currentLocation.Y;

    const auto targetX = this->currentTarget.X;
    const auto targetY = this->currentTarget.Y;

    const float diffX = calculateDiff(currentX, targetX);
    const float diffY = calculateDiff(currentY, targetY);

    // Проверяем угол по У
    if (diffY == 0) {
        return
    }
    else {
        float currentAngle = this->currentAngle;
        float targetAngle = abs(tan(diffY/diffX));
        number = ceil((targetAngle - currentAngle) / 13);
        if (targetAngle != currentAngle) {
            if (targetAngle > currentAngle) {
                for (int i = 0; i < number; i++) {
                    MotionModule.execute(Left);
                }
                
            }
            else {
                for (int i = 0; i < number; i++) {
                    MotionModule.execute(Right);
                }
            }
            vTaskDelay(pdMS_TO_TICKS(1000));
            GlobalLocationManager.disableUpdates = true;
        }

    }
    //Так ли сохраняется угол?
    this->currentAngle = targetAngle;
    return

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

    //Высчитываем скок надо проехать прямо
    const auto currentX = GlobalLocationManager.currentLocation.X;
    const auto currentY = GlobalLocationManager.currentLocation.Y;

    const auto targetX = this->currentTarget.X;
    const auto targetY = this->currentTarget.Y;
    
    const float diffX = calculateDiff(currentX, targetX);
    const float diffY = calculateDiff(currentY, targetY);

    const float diff = sqrt(diffX * diffX + diffY * diffY);
    
    if (diff > 0) {
            GlobalLocationManager.disableUpdates = false;
            MotionModule.execute(MoveForward);
            vTaskDelay(pdMS_TO_TICKS(100));
       
    } else {
        this->hasCurrentTarget = false;
        this->needStop = true;
    }
}