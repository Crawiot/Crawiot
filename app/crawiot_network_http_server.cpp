#include "crawiot_network.h"
#include "crawiot_traces.h"
#include "crawiot_main_page.h"
#include "HTTP_Method.h"
#include "crawiot_location.h"
#include "crawiot_mediator.h"

WebServer webServer(80);

void handlePostTargetRequest();
void handleGetTracesRequest();

bool Network::start_http_server() {

    webServer.on(("/"), []() {
        webServer.send(200, "text/html", CrawiotIndexPage);
    });

    webServer.on("/api/target", HTTP_POST, handlePostTargetRequest);

    webServer.on("/api/traces", handleGetTracesRequest);


    webServer.begin();
    GlobalTracer.send_trace("HTTP server started");
    return true;
}

void handlePostTargetRequest() {
    const int x = webServer.arg("X").toInt();
    const int y = webServer.arg("Y").toInt();
    const Coordinates coordinates = {
            .X = x,
            .Y = y
    };
    GlobalTracer.send_trace("Before push");
    const bool wasPushed = ModulesMediator.push_target(coordinates);
    GlobalTracer.send_trace("After push");
    String locationHeaderValue = "/?X=";
    locationHeaderValue.concat(x);

    locationHeaderValue.concat("&Y=");
    locationHeaderValue.concat(y);

    locationHeaderValue.concat("&success=");
    locationHeaderValue.concat(wasPushed ? "true" : "false");

    webServer.sendHeader("location", locationHeaderValue);
    webServer.send(302);
}

void handleGetTracesRequest() {
    webServer.send(200, "text/plain",GlobalTracer.get_traces());
}