#include "crawiot_network.h"
#include "crawiot_traces.h"
#include "crawiot_mediator.h"

Network NetworkModule = Network();

const char *CRAWIOT_HOST_NAME = "crawiot.lan";

void Network::setup() {
    if (!this->enable_wifi(CRAWIOT_HOST_NAME, "12345678")) {
        GlobalTracer.send_trace("Failed to enable Wi-Fi");
        return;
    }

    if (!this->enable_dns(CRAWIOT_HOST_NAME)){
        GlobalTracer.send_trace("Failed to enable DNS");
    }

    if (!this->start_http_server()) {
        GlobalTracer.send_trace("Failed to start http server");
        return;
    }

    GlobalTracer.send_trace("Network module initialized");
}

void Network::task() {
    while (1) { 
        this->dnsServer.processNextRequest(); 
    }
}

