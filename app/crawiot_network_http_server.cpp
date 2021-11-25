#include "crawiot_network.h"
#include "crawiot_traces.h"
#include "HTTP_Method.h"
#include "crawiot_location.h"
#include "crawiot_mediator.h"
#include "ArduinoJson.hpp"
#include "crawiot_motion.h"

ARDUINOJSON_NAMESPACE::StaticJsonDocument<1024> doc;

WebServer webServer(80);

void handlePostSubtargetsRequest();

void handleGetTracesRequest();

void handleGetLocationRequest();

void clearDocAndBadRequest();

bool Network::startHttpServer(const Config &config) {

    webServer.on("/api/subtargets", HTTP_POST, handlePostSubtargetsRequest);
    webServer.on("/api/traces", handleGetTracesRequest);
    webServer.on("/api/location", handleGetLocationRequest);
    if (config.enableMotionApi) {
        registerMotionApi();
    }

    webServer.begin();
    GlobalTracer.sendTrace("HTTP server started");
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

    const bool wasPushed = ModulesMediator.pushSubtargets(container);

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
    webServer.send(200, "text/plain", GlobalTracer.getTraces());
}

void handleGetLocationRequest() {
    ARDUINOJSON_NAMESPACE::StaticJsonDocument<64> bodyDoc;
    auto jsonDoc = bodyDoc.to<ArduinoJson::JsonObject>();
    jsonDoc["X"] = GlobalLocationManager.currentLocation.X;
    jsonDoc["Y"] = GlobalLocationManager.currentLocation.Y;
    String body = "";
    serializeJson(jsonDoc, body);
    webServer.send(200, "application/json", body);
}
