#if CONFIG_FREERTOS_UNICORE
#define ARDUINO_RUNNING_CORE 0
#else
#define ARDUINO_RUNNING_CORE 1
#endif

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include "crawiot_traces.h"
#include "crawiot_network.h"
#include "crawiot_tactical.h"
#include "crawiot_strategic.h"
#include "crawiot_mediator.h"


void crawiot_setup() {
    GlobalTracer.setup();
    NetworkModule.setup();
    ModulesMediator.setup();
    
    xTaskCreatePinnedToCore(
            NetworkModule.task, "NetworkModule", 1024, NULL, 3, NULL, ARDUINO_RUNNING_CORE);

    xTaskCreatePinnedToCore(
            StrategicModule.task, "StrategicModule", 1024, NULL, 2, NULL, ARDUINO_RUNNING_CORE);

    xTaskCreatePinnedToCore(
            TacticalModule.task, "TacticalModule", 1024, NULL, 1, NULL, ARDUINO_RUNNING_CORE);
}

void crawiot_loop() {
    GlobalTracer.send_trace("test trace");
    while (1) {

    }
}