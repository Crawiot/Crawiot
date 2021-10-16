#ifndef Crawiot_Network_h
#define Crawiot_Network_h

#include <DNSServer.h>

class Network {

public:
    [[noreturn]] static void task(void *pvParameters);

    void setup();

    void task();

private:
    bool enable_wifi(const char *ssid, const char *passphrase);
    bool enable_dns(const char* hostName);
    bool start_http_server();
    
    DNSServer dnsServer;
    
    IPAddress ipAddress = IPAddress().fromString("192.168.4.1");
};

extern Network NetworkModule;

#endif