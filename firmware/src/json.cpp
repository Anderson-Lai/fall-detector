#include <ArduinoJson.h>

#include "json.hpp"

String SerializeAlert(const Alert &alert) {
    JsonDocument doc;

    doc["device_id"] = alert.DeviceID;
    doc["alert_type"] = alert.AlertType;

    String output;
    serializeJson(doc, output);

    return output;
}