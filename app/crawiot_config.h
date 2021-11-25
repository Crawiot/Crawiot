#ifndef APP_CRAWIOT_CONFIG_H
#define APP_CRAWIOT_CONFIG_H

struct Config {
    const char* wiFiPassword;
    const char* hostName;
    const char* deviceIp;
    const int firstSpeedDegree;
    const bool enableMotionApi;
};

#endif //APP_CRAWIOT_CONFIG_H
