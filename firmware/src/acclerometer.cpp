#include <Arduino.h>

#include "accelerometer.hpp"

Accelerometer::Accelerometer(uint8_t xPin, uint8_t yPin, uint8_t zPin, 
    uint8_t gselectPin, AccelerometerMode mode)
    : m_xPin(xPin), m_yPin(yPin), m_zPin(zPin), m_gselectPin(gselectPin), m_mode(mode) {

    pinMode(xPin, INPUT);
    pinMode(yPin, INPUT);
    pinMode(zPin, INPUT);
    pinMode(gselectPin, OUTPUT);

    analogSetPinAttenuation(xPin, ADC_11db);
    analogSetPinAttenuation(yPin, ADC_11db);
    analogSetPinAttenuation(zPin, ADC_11db);

    m_mode == AccelerometerMode::LOW_ACCEL ? digitalWrite(gselectPin, LOW) 
        : digitalWrite(gselectPin, HIGH);
}

Accelerometer::Accelerometer(uint8_t xPin, uint8_t yPin, uint8_t zPin, 
    uint8_t gselectPin, AccelerometerMode mode, bool isDebug)
    : Accelerometer(xPin, yPin, zPin, gselectPin, mode) {
    m_isDebug = isDebug;
}

AccelerometerMode Accelerometer::GetMode() const {
    return m_mode;
}

void Accelerometer::SetMode(AccelerometerMode mode) {
    m_mode = mode;
}

double Accelerometer::GetX() const {
    return m_x;
}

double Accelerometer::GetY() const {
    return m_y;
}

double Accelerometer::GetZ() const {
    return m_z;
}

std::array<double, 3> Accelerometer::GetAccelerations() {
    ReadVoltages();
    return { m_x, m_y, m_z };
}

double Accelerometer::GetAcclerationMagnitude() {
    ReadVoltages();
    return sqrt(m_x * m_x + m_y * m_y + m_z * m_z);
}

bool Accelerometer::IsDebug() const {
    return m_isDebug;
}

void Accelerometer::SetDebug(bool isDebug) {
    m_isDebug = isDebug;
}

void Accelerometer::ReadVoltages() {
    uint32_t voltageX = analogReadMilliVolts(m_xPin);
    uint32_t voltageY = analogReadMilliVolts(m_yPin);
    uint32_t voltageZ = analogReadMilliVolts(m_zPin);

    if (m_isDebug) {
        Serial.printf("X: %lu mV | Y: %lu mV | Z: %lu mV\n",
            (unsigned long)voltageX,
            (unsigned long)voltageY,
            (unsigned long)voltageZ);
    }

    VoltagesToGs(std::array<uint32_t, 3>{
        analogReadMilliVolts(m_xPin),
        analogReadMilliVolts(m_yPin),
        analogReadMilliVolts(m_zPin)
    });

    GsToAccelerations();
    ApplyOffsets();
}

void Accelerometer::VoltagesToGs(const std::array<uint32_t, 3>& voltages) {
    double conversion = (m_mode == AccelerometerMode::LOW_ACCEL) 
        ? LOW_ACCEL_VOLTS_MV_PER_G : HIGH_ACCEL_VOLTS_MV_PER_G;
    
    m_x = (static_cast<double>(voltages[0]) - ZERO_G_X_VOLTAGE_MV) / conversion;
    m_y = (static_cast<double>(voltages[1]) - ZERO_G_Y_VOLTAGE_MV) / conversion;
    m_z = (static_cast<double>(voltages[2]) - ZERO_G_Z_VOLTAGE_MV) / conversion;
}

void Accelerometer::GsToAccelerations() {
    m_x *= GRAVITY;
    m_y *= GRAVITY;
    m_z *= GRAVITY;
}

void Accelerometer::ApplyOffsets() {
    if (m_mode == AccelerometerMode::LOW_ACCEL) {
        m_x -= X_LOW_OFFSET;
        m_y -= Y_LOW_OFFSET;
        m_z -= Z_LOW_OFFSET;
    } else {
        m_x -= X_HIGH_OFFSET;
        m_y -= Y_HIGH_OFFSET;
        m_z -= Z_HIGH_OFFSET;
    }
}