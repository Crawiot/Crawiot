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


Strategic StrategicModule = Strategic();
Tactical TacticalModule = Tactical();
Network NetworkModule = Network();

void crawiotSetup() {

    const Config config = {
            .wiFiPassword = "12345678",
            .hostName = "crawiot.lan",
            .deviceIp = "192.168.4.1",
            .firstSpeedDegree = 120,
    };
    GlobalTracer.setup();
    GlobalLocationManager.currentLocation.X = 0;
    GlobalLocationManager.currentLocation.Y = 0;
    GlobalLocationManager.currentAngle = 0;
    
    NetworkModule.setup(config);
    MotionModule.setup(config);

    ModulesMediator.setup();

    xTaskCreatePinnedToCore([](void *) {
        NetworkModule.task();
    }, "NetworkModule", 1024 * 3, NULL, 1, NULL, ARDUINO_RUNNING_CORE);

    xTaskCreatePinnedToCore([](void *) {
        StrategicModule.task();
    }, "StrategicModule", 1024, NULL, 3, NULL, ARDUINO_RUNNING_CORE);

    xTaskCreatePinnedToCore([](void *) {
        TacticalModule.task();
    }, "TacticalModule", 1024, NULL, 2, NULL, ARDUINO_RUNNING_CORE);
    
    xTaskCreatePinnedToCore([](void *) {
        MotionModule.task();
    }, "MotionModule", 1024, NULL, 1, NULL, ARDUINO_RUNNING_CORE);
}

void crawiotLoop() {
}
