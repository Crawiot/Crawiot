#ifndef APP_CRAWIOT_LOCATION_H
#define APP_CRAWIOT_LOCATION_H

struct Coordinates {
    int X;
    int Y;
};

class LocationManager {
public:
    Coordinates current_location;
};

extern LocationManager GlobalLocationManager;

#endif //APP_CRAWIOT_LOCATION_H
