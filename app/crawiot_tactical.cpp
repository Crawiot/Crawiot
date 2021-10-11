#include "crawiot_tactical.h"
#include "Arduino.h"
#include "crawiot_traces.h"

void Tactical::reach_target(const Coordinates target_coordinates[], int count) {

}

void Tactical::task(void *pvParameters) {
    while (1) {
        GlobalTracer.send_trace("Tactical module is running");
        delay(1000);
    }
}