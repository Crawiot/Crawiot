#include "crawiot_network.h"
#include "crawiot_traces.h"

bool enable_wifi() {
    send_trace("Wi-fi enabled");
    return true;
}