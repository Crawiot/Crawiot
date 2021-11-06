#ifndef CRAWIOT_CIRCULARBUFFER_H
#define CRAWIOT_CIRCULARBUFFER_H

#include <Arduino.h>
#define TRACES_BUFFER_LENGTH 60

class CircularBuffer {
public:
    void add(String message);
    String getCombinedTrace();

private:
    int recordIndex = 0;
    int currentBufferSize = 0;
    String buffer[TRACES_BUFFER_LENGTH];
};

#endif