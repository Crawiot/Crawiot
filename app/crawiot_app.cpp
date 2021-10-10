#include "crawiot_traces.h"
#include "crawiot_network.h"

void crawiot_setup() {
    GlobalTracer.setup();
    setup_network();
}

void crawiot_loop() {
    GlobalTracer.send_trace("test trace");
    while (1){
        
    }
}