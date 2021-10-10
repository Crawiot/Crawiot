#ifndef Crawiot_Network_h
#define Crawiot_Network_h

class Network {
    
public:
    void setup();

private:
    bool enable_wifi();

    bool start_http_server();
};

extern Network NetworkModule; 

#endif