#ifndef Crawiot_Trace_h
#define Crawiot_Trace_h

#include <Arduino.h>

class Tracer {
public:
    void setup();
    void send_trace(String message);
    void light_default_led();
};

extern Tracer GlobalTracer;

#endif
