#ifndef CRAWIOT_CIRCULARBUFFER_H
#define CRAWIOT_CIRCULARBUFFER_H

#include <Arduino.h>
#define TRACES_BUFFER_LENGTH 20

class CircularBuffer {
public:
    void add(String message);
    String get_combined_trace();

private:
    int recordIndex = 0;
    int currentBufferSize = 0;
    String buffer[TRACES_BUFFER_LENGTH];
};

#endif