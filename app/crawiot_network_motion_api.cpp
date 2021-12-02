
#include "crawiot_network.h"
#include "crawiot_motion.h"
#include "crawiot_traces.h"

int getUnits() {
    return webServer.arg("units").toInt();
}

void response(const bool result) {
    if (result) {
        webServer.send(200);
    } else {
        webServer.send(400);
    }
}

void handleMotionMove() {
    const auto units = getUnits();
    const auto result = MotionModule.motionApi.move(units);
    String message = "Motion Api. Move ";
    message.concat(units);
    GlobalTracer.sendTrace(message);
    response(result);
}

void handleMotionRotate() {
    const auto units = getUnits();
    const auto result = MotionModule.motionApi.rotate(units);
    String message = "Motion Api. Rotate ";
    message.concat(units);
    GlobalTracer.sendTrace(message);
    response(result);
}

void Network::registerMotionApi() {
    webServer.on("/api/motion/move", HTTP_POST, handleMotionMove);
    webServer.on("/api/motion/rotate", HTTP_POST, handleMotionRotate);
}