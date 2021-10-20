#include "crawiot_traces.h"

Tracer GlobalTracer = Tracer();

void Tracer::send_trace(String message) {
    this->log.add(message);
    Serial.println(message);
}

void Tracer::setup() {
    pinMode(LED_BUILTIN, OUTPUT);
    Serial.begin(9600);
    delay(1000);
}

void Tracer::light_default_led() {
    digitalWrite(LED_BUILTIN, HIGH);
}