#ifndef CRAWIOT_CIRCULARBUFFER_H
#define CRAWIOT_CIRCULARBUFFER_H

#include <Arduino.h>

const int traceBufferLength = 100;

class CircularBuffer {
public:
    void add(String message);
    String send_trace();

private:
    int recordIndex = 0;
    int currentBufferSize = 0;
    String buffer[traceBufferLength];
};

#endif