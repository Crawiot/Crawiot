#include "crawiot_traces.h"

void setup_traces() {
    pinMode(LED_BUILTIN, OUTPUT);
    Serial.begin(9600);
    for (int i = 0; i < 10; ++i) {
        // wait for serial port to connect
        delay(100);

        if (Serial) {
            return;
        }
    }

    light_default_led();
}

void send_trace(String message) {
    Serial.println(message);
}

void light_default_led() {
    digitalWrite(LED_BUILTIN, HIGH);
}