#include "crawiot_network.h"
#include "crawiot_traces.h"

void Network::setup(const Config& config) {
    this->deviceIp.fromString(config.DeviceIp);
    
    if (!this->enableWifi(config.HostName, config.WiFiPassword)) {
        GlobalTracer.sendTrace("Failed to enable Wi-Fi");
        return;
    }

    if (!this->enableDns(config.HostName)){
        GlobalTracer.sendTrace("Failed to enable DNS");
    }

    if (!this->startHttpServer()) {
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

