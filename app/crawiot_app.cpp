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
#include "crawiot_motion.h"


void crawiot_setup() {

    const Config config = {
            .WiFiPassword = "12345678",
            .HostName = "crawiot.lan",
            .DeviceIp = "192.168.4.1",
            .FirstSpeedDegree = 45
    };

    GlobalTracer.setup();
    NetworkModule.setup(config);
    MotionModule.setup(config);

    ModulesMediator.setup();

    xTaskCreatePinnedToCore([](void *) {
        NetworkModule.task();
    }, "NetworkModule", 1024 * 3, NULL, 3, NULL, ARDUINO_RUNNING_CORE);

    xTaskCreatePinnedToCore([](void *) {
        StrategicModule.task();
    }, "StrategicModule", 1024, NULL, 2, NULL, ARDUINO_RUNNING_CORE);

    xTaskCreatePinnedToCore([](void *) {
        TacticalModule.task();
    }, "TacticalModule", 1024, NULL, 1, NULL, ARDUINO_RUNNING_CORE);
}

void crawiot_loop() {
}