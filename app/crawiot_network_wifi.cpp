#include "crawiot_network.h"
#include "crawiot_traces.h"

bool enable_wifi() {
    GlobalTracer.send_trace("Wi-fi enabled");
    return true;
}