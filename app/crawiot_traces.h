#ifndef Crawiot_Trace_h
#define Crawiot_Trace_h

#include <Arduino.h>
#include "crawiot_circularbuffer.h"

class Tracer {
public:
    void setup();
    void send_trace(String message);
    String get_traces();
    void light_default_led();

private:
    CircularBuffer log;
};

extern Tracer GlobalTracer;

#endif
