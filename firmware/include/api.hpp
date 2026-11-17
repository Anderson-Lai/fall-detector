#pragma once

#include <WiFiClientSecure.h>

class Api {
private:
    const char* m_apiUrl;
    const char* m_certificate;

    const char* m_apiKey;
    const char* m_deviceId;

    WiFiClientSecure m_secureClient;
public:
    Api(const char *apiUrl, const char *certificate, const char *apiKey, const char *deviceId);
    bool SendAlert(const char* alertType);
};