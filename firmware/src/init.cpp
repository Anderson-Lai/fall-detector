#include <Arduino.h>
#include <WiFi.h>
#include <time.h>

#include "init.hpp"
#include "credentials.hpp"

void Init::InitSerial(const unsigned long baudRate) {
    Serial.begin(baudRate);
    Serial.println("Starting...");
}

bool Init::ConnectToWifi() {
    WiFi.mode(WIFI_STA);
    WiFi.setSleep(false);

    WiFi.disconnect(true, true);
    delay(1000);

    Serial.println("Scanning for WiFi networks...");
    int networks = WiFi.scanNetworks();
    for (int i = 0; i < networks; i++) {
        Serial.print("SSID: ");
        Serial.print(WiFi.SSID(i));

        Serial.print(" | RSSI: ");
        Serial.print(WiFi.RSSI(i));

        Serial.print(" | Channel: ");
        Serial.println(WiFi.channel(i));
    }

    Serial.println();
    WiFi.begin(WifiCredentials::SSID, WifiCredentials::PASSWORD);
    Serial.print("Connecting to Wi-Fi");

    for (uint32_t i = 0; i < Init::WIFI_CONNECT_MAX_RETRIES; ++i) {
        if (WiFi.status() == WL_CONNECTED) {
            break;
        }

        delay(Init::WIFI_CONNECT_RETRY_TIMEOUT_MS);
        Serial.print(".");

        if (i == Init::WIFI_CONNECT_MAX_RETRIES - 1) {
            Serial.println();
            Serial.println("Failed to connect to Wi-Fi");
            return false;
        }
    }

    Serial.println();
    Serial.println("Connected to Wi-Fi!");

    Serial.print("SSID: ");
    Serial.println(WiFi.SSID());

    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());

    Serial.print("Signal Strength (RSSI): ");
    Serial.print(WiFi.RSSI());
    Serial.println(" dBm");

    return true;
}

bool Init::SynchronizeTime() {
    configTime(0, 0, "pool.ntp.org", "time.nist.gov");

    Serial.print("Synchronizing time");

    for (uint32_t i = 0; i < Init::TIME_SYNC_MAX_RETRIES; ++i) {
        struct tm timeinfo;
        if (getLocalTime(&timeinfo, Init::TIME_SYNC_RETRY_TIMEOUT_MS)) {
            Serial.println();
            Serial.println("Time synchronized!");
            return true;
        }

        Serial.print(".");
    }

    Serial.println();
    Serial.println("Failed to synchronize time");
    return false;
}