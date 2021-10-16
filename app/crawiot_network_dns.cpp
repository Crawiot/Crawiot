#include "crawiot_network.h"

bool Network::enable_dns(const char* hostName) {
    this->dnsServer = DNSServer();
    return this->dnsServer.start(53, hostName, this->deviceIp);
}