#ifndef APP_CRAWIOT_STRATEGIC_H
#define APP_CRAWIOT_STRATEGIC_H

#include "crawiot_location.h"
#include "crawiot_mediator.h"

class Strategic {
public:
    [[noreturn]] void task();
private:
    void process_subtargets(const SubtargetsContainer);
};

#endif //APP_CRAWIOT_STRATEGIC_H
