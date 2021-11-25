#include "crawiot_network.h"
#include "crawiot_traces.h"

void Network::setup(const Config& config) {
    this->deviceIp.fromString(config.deviceIp);
    
    if (!this->enableWifi(config.hostName, config.wiFiPassword)) {
        GlobalTracer.sendTrace("Failed to enable Wi-Fi");
        return;
    }

    if (!this->enableDns(config.hostName)){
        GlobalTracer.sendTrace("Failed to enable DNS");
    }

    if (!this->startHttpServer(config)) {
        GlobalTracer.sendTrace("Failed to start http server");
        return;
    }

    GlobalTracer.sendTrace("Network module initialized");
}

[[noreturn]] void Network::task() {
    while (1) { 
        this->dnsServer.processNextRequest();
        webServer.handleClient();
    }
}

