cmake_minimum_required(VERSION 3.20)
project(app)
add_compile_definitions(UBRRH)
set(CMAKE_CXX_STANDARD 14)

include_directories("C:/Program Files/WindowsApps/ArduinoLLC.ArduinoIDE_1.8.51.0_x86__mdqgnx93n4wtt/hardware/arduino/avr/cores/arduino")


add_library(app
        crawiot_network_http_server.cpp
        crawiot_network_wifi.cpp
        crawiot_traces.cpp
        crawiot_network.cpp
        crawiot_app.cpp
        crawiot_strategic.cpp crawiot_strategic.h crawiot_mediator.cpp crawiot_mediator.h common.h)
