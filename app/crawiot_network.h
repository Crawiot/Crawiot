#ifndef Crawiot_Network_h
#define Crawiot_Network_h

#include "crawiot_config.h"
#include <DNSServer.h>
#include <WebServer.h>

extern WebServer webServer;

class Network {

public:
    void setup(const Config&);

    [[noreturn]] void task();

private:
    bool enableWifi(const char *ssid, const char *passphrase);

    bool enableDns(const char *hostName);

    bool startHttpServer(const Config&);
    
    void registerMotionApi();

    DNSServer dnsServer;
    
    IPAddress deviceIp;
};

#endif