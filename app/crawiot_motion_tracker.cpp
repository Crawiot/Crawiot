#include <Arduino.h>
#include "crawiot_motion_tracker.h"
#include "crawiot_location.h"
#include "crawiot_traces.h"

static const int HALL_PIN_D15 = 15;

static const bool TRUE = true; 
volatile xQueueHandle location_updates;

void IRAM_ATTR isr() {
    xQueueSendFromISR(location_updates, &TRUE, NULL);
};

void Tracker::setup(const Config &config) {
    pinMode(HALL_PIN_D15, INPUT);
    attachInterrupt(HALL_PIN_D15, isr, FALLING);

    location_updates = xQueueCreate(2, sizeof(bool));
}

[[noreturn]] void Tracker::task() {
    while (1) {
        bool update;
        const bool received = xQueueReceive(
                                      location_updates,
                                      &update,
                                      portMAX_DELAY) == pdTRUE;

        if (received) {
            GlobalLocationManager.current_location.X += 1;
            
            String message = "Motion. Current coordinate ";
            message.concat(GlobalLocationManager.current_location.X);
            GlobalTracer.send_trace(message);
        }
    }
}