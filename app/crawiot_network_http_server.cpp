#include "crawiot_network.h"
#include "crawiot_traces.h"

bool start_http_server() {
    GlobalTracer.send_trace("HTTP server started");
    return true;
}