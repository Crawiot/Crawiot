#include "crawiot_network.h"
#include "crawiot_traces.h"

void setup_network() {
    if (!enable_wifi()) {
        send_trace("Failed to enable Wi-Fi module");
        return;
    }

    if (!start_http_server()){
        send_trace("Failed to start http server");
        return;
    }

    send_trace("Network module initialized");
}