#include "crawiot_circularbuffer.h"
#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"

const int traceBufferLength = TRACES_BUFFER_LENGTH;

static auto bufferSemaphore = xSemaphoreCreateBinary();

void CircularBuffer::add(String message) {
    xSemaphoreTake(bufferSemaphore, pdMS_TO_TICKS(50));
    
    if (this->currentBufferSize < traceBufferLength) 
        ++this->currentBufferSize;

    this->buffer[this->recordIndex] = message;
    ++this->recordIndex;
    this->recordIndex %= traceBufferLength;

    xSemaphoreGive(bufferSemaphore);
}

String CircularBuffer::getCombinedTrace() {

    if (!this->currentBufferSize) return String("There's no traces");

    int firstIndex = (traceBufferLength + this->recordIndex - this->currentBufferSize) % traceBufferLength;
    String finalLog = this->buffer[firstIndex] + "\r\n";
    for (int i = firstIndex + 1; i < firstIndex + this->currentBufferSize; i++) {
        int ind = i % traceBufferLength;
        finalLog.concat(this->buffer[ind]);
        finalLog.concat("\r\n");
    }
    return finalLog;
}