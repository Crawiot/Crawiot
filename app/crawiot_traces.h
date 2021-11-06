#ifndef Crawiot_Trace_h
#define Crawiot_Trace_h

#include <Arduino.h>
#include "crawiot_circularbuffer.h"

class Tracer {
public:
    void setup();
    void sendTrace(String message);
    String getTraces();
    void lightDefaultLed();

private:
    CircularBuffer log;
};

extern Tracer GlobalTracer;

#endif
