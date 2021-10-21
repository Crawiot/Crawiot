#include "crawiot_network.h"
#include "crawiot_traces.h"
#include "crawiot_main_page.h"

WebServer webServer(80);

bool Network::start_http_server() {

    webServer.on(("/"), [] () {
        webServer.send(200, "text/html", CrawiotIndexPage);
    });
    webServer.begin();
    
    GlobalTracer.send_trace("HTTP server started");

    return true;
}