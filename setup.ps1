param([string]$CrawiotDir = "") 

if (!([Security.Principal.WindowsPrincipal][Security.Principal.WindowsIdentity]::GetCurrent()).IsInRole([Security.Principal.WindowsBuiltInRole] "Administrator")) { 
    $location = Get-Location;
    Start-Process powershell.exe "-NoProfile -ExecutionPolicy Bypass -File `"$PSCommandPath`" -CrawiotDir $location" -Verb RunAs; 
    exit 
}


Set-Location $CrawiotDir;

$arduinoFolder = (Get-ChildItem -Path "C:\Program Files\WindowsApps\*" -Directory |
    Where-Object { $_.Name.StartsWith("ArduinoLLC.ArduinoIDE") } |
    Select-Object -Last 1).Name;


$coresArduinoFolder = "C:/Program Files/WindowsApps/$arduinoFolder/hardware/arduino/avr/cores/arduino";
$docementsFolder = [Environment]::GetFolderPath("MyDocuments");
$esp32FreeRTOSFolder = ((Get-ChildItem -Path "$docementsFolder\ArduinoData\packages\esp32" -Recurse -Filter "FreeRTOS.h") |
    Where-Object { $_.DirectoryName.Contains("sdk\include\freertos") }).DirectoryName.Replace("\", "/").Replace("freertos/freertos", "freertos");

$cmakeList = @"
cmake_minimum_required(VERSION 3.20)
project(app)
add_compile_definitions(UBRRH)
set(CMAKE_CXX_STANDARD 14)

include_directories("$coresArduinoFolder")
include_directories("$esp32FreeRTOSFolder")

add_library(app
        crawiot_network_http_server.cpp
        crawiot_network_wifi.cpp
        crawiot_traces.cpp
        crawiot_network.cpp
        crawiot_app.cpp
        crawiot_strategic.cpp
        crawiot_strategic.h
        crawiot_mediator.cpp
        crawiot_mediator.h
        crawiot_tactical.cpp
        crawiot_tactical.h
        crawiot_location.cpp
        crawiot_location.h
        crawiot_motion.cpp
        crawiot_motion.h
        )
"@
Set-Content ".\app\CMakeLists.txt" -Value $cmakeList