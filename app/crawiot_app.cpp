#include "crawiot_traces.h"
#include "crawiot_network.h"
#include "crawiot_tactical.h"

void crawiot_setup() {
    GlobalTracer.setup();
    NetworkModule.setup();
}

void crawiot_loop() {
    GlobalTracer.send_trace("test trace");
    while (1){
        
    }
}