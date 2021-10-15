#ifndef Crawiot_Trace_h
#define Crawiot_Trace_h

#include <Arduino.h>

const int traceBufferLength = 100;

class CircularBuffer {
public:
    void add(String message);

private:
    int recordIndex = 0;
    int currentBufferSize = 0;
    String buffer[traceBufferLength];
};

class Tracer {
public:
    void setup();
    void send_trace(String message);
    void light_default_led();

private:
    CircularBuffer log;
};

extern Tracer GlobalTracer;

#endif
