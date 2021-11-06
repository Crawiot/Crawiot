#include "crawiot_traces.h"

Tracer GlobalTracer = Tracer();

void Tracer::sendTrace(String message) {
    this->log.add(message);
    Serial.println(message);
}

void Tracer::setup() {
    pinMode(LED_BUILTIN, OUTPUT);
    Serial.begin(9600);
    delay(1000);
}

void Tracer::lightDefaultLed() {
    digitalWrite(LED_BUILTIN, HIGH);
}

String Tracer::getTraces() {
    return this->log.getCombinedTrace();
}