#include "crawiot_network.h"
#include "crawiot_traces.h"
#include "crawiot_mediator.h"

Network NetworkModule = Network();

void Network::setup() {
    if (!this->enable_wifi()) {
        GlobalTracer.send_trace("Failed to enable Wi-Fi module");
        return;
    }

    if (!this->start_http_server()) {
        GlobalTracer.send_trace("Failed to start http server");
        return;
    }

    GlobalTracer.send_trace("Network module initialized");
}

[[noreturn]] void Network::task(void *pvParameters) {
    while (1) {
        GlobalTracer.send_trace("Network module is running");
        const Coordinates cords = {
                .X = 5,
                .Y = 3.1
        };
        ModulesMediator.push_target(cords);
        delay(10000);
    }
}