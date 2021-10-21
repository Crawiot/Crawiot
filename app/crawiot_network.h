#ifndef Crawiot_Network_h
#define Crawiot_Network_h

#include "crawiot_config.h"
#include <DNSServer.h>
#include <WebServer.h>

class Network {

public:
    void setup(const Config&);

    [[noreturn]] void task();

private:
    bool enable_wifi(const char *ssid, const char *passphrase);

    bool enable_dns(const char *hostName);

    bool start_http_server();

    DNSServer dnsServer;

    WebServer webServer;
    
    IPAddress deviceIp;
};

extern Network NetworkModule;
#endif