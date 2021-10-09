#include "crawiot_traces.h"

void setup_traces() {
    Serial.begin(9600);
}

void send_trace(String message) {
    Serial.println(message);
}
