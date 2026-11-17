#pragma once

struct Alert {
    const char *DeviceID;
    const char *AlertType;
};

struct Provision {
    const char *DeviceID;
    const char *APIKey;
};