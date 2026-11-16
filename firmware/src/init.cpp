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

bool Init::ConnectToWifi() {
    WiFi.mode(WIFI_STA);
    WiFi.begin(WifiCredentials::SSID, WifiCredentials::PASSWORD);
    Serial.print("Connecting to Wi-Fi");

    for (int i = 0; i < 10; ++i) {
        if (WiFi.status() == WL_CONNECTED) {
            break;
        }

        delay(750);
        Serial.print(".");

        if (i == 9) {
            Serial.println();
            Serial.println("Failed to connect to Wi-Fi");
            return false;
        }
    }

    Serial.println();
    Serial.println("Connected to Wi-Fi");

    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());

    Serial.print("Signal Strength (RSSI): ");
    Serial.print(WiFi.RSSI());
    Serial.println(" dBm");

    return true;
}