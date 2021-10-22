#include "crawiot_network.h"
#include "crawiot_traces.h"
#include "crawiot_main_page.h"
#include "HTTP_Method.h"
#include "crawiot_location.h"
#include "crawiot_mediator.h"

WebServer webServer(80);

bool Network::start_http_server() {

    webServer.on(("/"), []() {
        webServer.send(200, "text/html", CrawiotIndexPage);
    });

    webServer.on("/api/target", HTTP_POST, []() {
        const int x = webServer.arg("X").toInt();
        const int y = webServer.arg("Y").toInt();
        const Coordinates coordinates = {
                .X = x,
                .Y = y
        };
        
        const bool wasPushed = ModulesMediator.push_target(coordinates);
        String locationHeaderValue = "/?X=";
        locationHeaderValue.concat(x);
        
        locationHeaderValue.concat("&Y=");
        locationHeaderValue.concat(y);

        locationHeaderValue.concat("&success=");
        locationHeaderValue.concat(wasPushed ? "true" : "false");
        
        webServer.sendHeader("location", locationHeaderValue);
        webServer.send(302);
    });


    webServer.begin();
    GlobalTracer.send_trace("HTTP server started");
    return true;
}