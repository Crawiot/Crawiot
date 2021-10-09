#include "crawiot_traces.h"
#include "crawiot_network.h"

void crawiot_setup() {
    setup_traces();
    setup_network();
}

void crawiot_loop() {
    send_trace("test trace");
    while (1){
        
    }
}