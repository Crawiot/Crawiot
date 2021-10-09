#include "crawiot_traces.h"

void crawiot_setup() {
    setup_traces();
}

void crawiot_loop() {
    send_trace("test trace");

    while (1){

    }
}