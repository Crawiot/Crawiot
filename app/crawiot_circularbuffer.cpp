#include "crawiot_circularbuffer.h"


void CircularBuffer::add(String message){
    
    if (this->currentBufferSize < traceBufferLength) ++this->currentBufferSize;
    
    this->buffer[this->recordIndex] = message;
    ++this->recordIndex;
    this->recordIndex %= traceBufferLength;
}

String CircularBuffer::send_trace() {

    if (!this->currentBufferSize) return String();


    int firstIndex = (traceBufferLength + this->recordIndex - this->currentBufferSize) % traceBufferLength;
    String finalLog = this->buffer[firstIndex] + "\r\n";
    for (int i = firstIndex + 1; i < firstIndex + this->currentBufferSize; i++){
        int ind = i % traceBufferLength;
        finalLog.concat(this->buffer[ind]);
    }
    return finalLog;
}