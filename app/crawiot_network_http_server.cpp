#include "crawiot_network.h"
#include "crawiot_traces.h"
#include <WebServer.h>
#include "crawiot_main_page.h"

WebServer server(80);

bool Network::start_http_server() {

    server.on(("/"), [] () {
        server.send(200, "text/html", CrawiotIndexPage);
    });
    server.begin();
    this->webServer = server;
    GlobalTracer.send_trace("HTTP server started");

    return true;
}