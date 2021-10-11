#include "crawiot_strategic.h"
#include "crawiot_traces.h"

Strategic StrategicModule = Strategic();

void Strategic::reach_target() {
    
}

void Strategic::reach_coordinates(const Coordinates coordinates) {
    
}

void Strategic::task(void *pvParameters) {
    while (1) {
        GlobalTracer.send_trace("Strategic module is running");
        delay(1000);
    }
}