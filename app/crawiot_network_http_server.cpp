#include "crawiot_network.h"
#include "crawiot_traces.h"
#include "crawiot_main_page.h"
#include "HTTP_Method.h"
#include "crawiot_location.h"
#include "crawiot_mediator.h"
#include "ArduinoJson.hpp"
#include "ArduinoJson/Document/StaticJsonDocument.hpp"

using namespace ARDUINOJSON_NAMESPACE;

WebServer webServer(80);
StaticJsonDocument<1024> doc;


void handlePostSubtargetsRequest();

void handleGetTracesRequest();

bool Network::start_http_server() {

    webServer.on(("/"), []() {
        webServer.send(200, "text/html", CrawiotIndexPage);
    });

    webServer.on("/api/subtargets", HTTP_POST, handlePostSubtargetsRequest);

    webServer.on("/api/traces", handleGetTracesRequest);


    webServer.begin();
    GlobalTracer.send_trace("HTTP server started");
    return true;
}

void handlePostSubtargetsRequest() {
    const auto body = webServer.arg("plain");
    deserializeJson(doc, body);
    const auto array = doc["subtargets"].as<ArduinoJson::JsonArray>();
    const auto size = array.size();
    Coordinates *subtargets = new Coordinates[size];
    for (size_t index = 0; index < size; index++) {
        const auto x = array.getElement(index)["x"].as<float>();
        const auto y = array.getElement(index)["y"].as<float>();
        subtargets[index] = {
                .X = x,
                .Y = y
        };;
    }

    const SubtargetsContainer container = {
            .subtargets = subtargets
    };

    const bool wasPushed = ModulesMediator.push_subtargets(container);
    doc.clear();

    if (wasPushed) {
        webServer.send(200);
    } else {
        webServer.send(500);
    }
}

void handleGetTracesRequest() {
    webServer.send(200, "text/plain", GlobalTracer.get_traces());
}