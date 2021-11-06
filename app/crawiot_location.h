#ifndef APP_CRAWIOT_LOCATION_H
#define APP_CRAWIOT_LOCATION_H

struct Coordinates {
    float X;
    float Y;
};

class LocationManager {
public:
    Coordinates currentLocation;
};

extern LocationManager GlobalLocationManager;

#endif //APP_CRAWIOT_LOCATION_H
