#include "crawiot_network.h"
#include "crawiot_traces.h"

bool Network::start_http_server() {
    GlobalTracer.send_trace("HTTP server started");
    return true;
}