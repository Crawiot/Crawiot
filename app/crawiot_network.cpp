#include "crawiot_network.h"
#include "crawiot_traces.h"

Network NetworkModule = Network();

void Network::setup(const Config& config) {
    this->deviceIp.fromString(config.DeviceIp);
    
    if (!this->enable_wifi(config.HostName, config.WiFiPassword)) {
        GlobalTracer.send_trace("Failed to enable Wi-Fi");
        return;
    }

    if (!this->enable_dns(config.HostName)){
        GlobalTracer.send_trace("Failed to enable DNS");
    }

    if (!this->start_http_server()) {
        GlobalTracer.send_trace("Failed to start http server");
        return;
    }

    GlobalTracer.send_trace("Network module initialized");
}

[[noreturn]] void Network::task() {
    while (1) { 
        this->dnsServer.processNextRequest();
        webServer.handleClient();
    }
}

