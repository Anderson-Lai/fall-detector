#include <Arduino.h>
#include <WiFi.h>

#include "init.hpp"
#include "credentials.hpp"

void Init::InitSerial(const unsigned long baudRate) {
    Serial.begin(baudRate);
    Serial.println("Starting...");
}

void Init::PulldownAllPins() {
    const uint8_t pins[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 20, 21 };
    for (uint8_t i = 0; i < sizeof(pins) / sizeof(uint8_t); ++i) {
        pinMode(pins[i], INPUT_PULLDOWN);
    }
}

void Init::ConnectToWifi() {
    WiFi.begin(WifiCredentials::SSID, WifiCredentials::PASSWORD);
    Serial.print("Connecting to Wi-Fi");
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println();
    Serial.println("Connected to Wi-Fi");

    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());

    Serial.print("Signal Strength (RSSI): ");
    Serial.print(WiFi.RSSI());
    Serial.println(" dBm");
}