#ifndef APP_CRAWIOT_CONFIG_H
#define APP_CRAWIOT_CONFIG_H

struct Config {
    const char* WiFiPassword;
    const char* HostName;
    const char* DeviceIp;
    const int FirstSpeedDegree;
    const int WheelRadius;
};

#endif //APP_CRAWIOT_CONFIG_H
