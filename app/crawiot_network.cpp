#include "crawiot_network.h"
#include "crawiot_traces.h"

Network NetworkModule = Network();

void Network::setup() {
    if (!this->enable_wifi()) {
        GlobalTracer.send_trace("Failed to enable Wi-Fi module");
        return;
    }

    if (!this->start_http_server()){
        GlobalTracer.send_trace("Failed to start http server");
        return;
    }

    GlobalTracer.send_trace("Network module initialized");
}