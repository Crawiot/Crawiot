#include "crawiot_network.h"
#include "crawiot_traces.h"
#include "HTTP_Method.h"
#include "crawiot_location.h"
#include "crawiot_mediator.h"
#include "ArduinoJson.hpp"

using namespace ARDUINOJSON_NAMESPACE;

WebServer webServer(80);
StaticJsonDocument<1024> doc;


void handlePostSubtargetsRequest();

void handleGetTracesRequest();

void clearDocAndBadRequest();

bool Network::startHttpServer() {

    webServer.on("/api/subtargets", HTTP_POST, handlePostSubtargetsRequest);

    webServer.on("/api/traces", handleGetTracesRequest);

    webServer.begin();
    GlobalTracer.SendTrace("HTTP server started");
    return true;
}

void handlePostSubtargetsRequest() {
    const auto body = webServer.arg("plain");
    deserializeJson(doc, body);

    const auto array = doc["subtargets"].as<ArduinoJson::JsonArray>();
    if (array.isNull()) {
        clearDocAndBadRequest();
        return;
    }

    const auto size = array.size();
    auto *subtargets = new Coordinates[size];
    for (size_t index = 0; index < size; index++) {
        subtargets[index] = {
                .X = array.getElement(index)["x"].as<float>(),
                .Y = array.getElement(index)["y"].as<float>()
        };
    }

    const SubtargetsContainer container = {
            .subtargets = subtargets,
            .size = size
    };

    const bool wasPushed = ModulesMediator.PushSubtargets(container);

    doc.clear();
    if (wasPushed) {
        webServer.send(200);
    } else {
        webServer.send(500);
    }
}

void clearDocAndBadRequest() {
    doc.clear();
    webServer.send(400);
}

void handleGetTracesRequest() {
    webServer.send(200, "text/plain", GlobalTracer.GetTraces());
}