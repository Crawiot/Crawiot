#include "crawiot_network.h"
#include "crawiot_traces.h"
#include <WiFi.h>

bool Network::enable_wifi(const char *ssid, const char *passphrase) {
    WiFi.mode(WIFI_AP);

    if (!WiFi.softAP(ssid, passphrase)) {
        GlobalTracer.send_trace("Failed to start Wi-fi");
        return false;
    }
    
    WiFi.softAPConfig(this->ipAddress, ipAddress, IPAddress(255, 255, 255, 0));

    GlobalTracer.send_trace("Wi-fi enabled");
    return true;
}