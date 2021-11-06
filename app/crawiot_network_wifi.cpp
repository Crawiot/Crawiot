#include "crawiot_network.h"
#include "crawiot_traces.h"
#include <WiFi.h>

bool Network::enableWifi(const char *ssid, const char *passphrase) {
    WiFi.mode(WIFI_AP);

    if (!WiFi.softAP(ssid, passphrase)) {
        GlobalTracer.sendTrace("Failed to start Wi-fi");
        return false;
    }
    
    delay(1000);
    WiFi.softAPConfig(this->deviceIp, deviceIp, IPAddress(255, 255, 255, 0));

    GlobalTracer.sendTrace("Wi-fi enabled");
    return true;
}