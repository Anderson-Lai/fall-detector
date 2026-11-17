#include <HTTPClient.h>
#include <WiFi.h>

#include "api.hpp"
#include "request_types.hpp"
#include "json.hpp"


Api::Api(const char *apiUrl, const char *certificate, const char *apiKey, const char *deviceId)
    : m_apiUrl(apiUrl), m_certificate(certificate), m_apiKey(apiKey), m_deviceId(deviceId) {
    m_secureClient.setCACert(m_certificate);
}

bool Api::SendAlert(const char *alertType) {
    HTTPClient http;
    if (!http.begin(m_secureClient, m_apiUrl)) {
        Serial.println("Failed to connect to API");
        return false;
    }

    http.addHeader("Content-Type", "application/json");
    http.addHeader("x-api-key", m_apiKey);

    Alert alert = {
        .DeviceID = m_deviceId,
        .AlertType = alertType,
    };

    String payload = JSON::SerializeAlert(alert);

    int httpResponseCode = http.POST(payload);
    if (httpResponseCode > 0) {

        Serial.printf("HTTP Status: %d\n", httpResponseCode);

        String response = http.getString();

        Serial.println("Server response:");
        Serial.println(response);

        http.end();

        return httpResponseCode >= 200 && httpResponseCode < 300;
    }

    Serial.print("HTTP request failed: ");
    Serial.println(http.errorToString(httpResponseCode));
    http.end();

    return httpResponseCode > 0 && httpResponseCode < 300;
}