#include <Arduino.h>
#include <cmath>

#include "accelerometer.hpp"

Accelerometer::Accelerometer(uint8_t xPin, uint8_t yPin, uint8_t zPin, 
        uint8_t gselectPin, AccelerometerMode mode, bool isDebug)
    : m_xPin(xPin), m_yPin(yPin), m_zPin(zPin), m_gselectPin(gselectPin), 
        m_mode(mode), m_isDebug(isDebug) {

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

AccelerometerMode Accelerometer::GetMode() const {
    return m_mode;
}

void Accelerometer::SetMode(AccelerometerMode mode) {
    m_mode = mode;
    m_mode == AccelerometerMode::LOW_ACCEL ? digitalWrite(m_gselectPin, LOW) 
        : digitalWrite(m_gselectPin, HIGH);
}

std::array<double, 3> Accelerometer::GetAccelerations() const {
    auto readings = ReadVoltages();
    readings = VoltagesToGs(readings);
    readings = GsToAccelerations(readings);
    readings = ApplyOffsets(readings);

    return readings;
}

double Accelerometer::GetAcclerationMagnitude() const {
    auto accelerations = GetAccelerations();
    return sqrt(accelerations[0] * accelerations[0] + 
        accelerations[1] * accelerations[1] + 
        accelerations[2] * accelerations[2]);
}

bool Accelerometer::IsDebug() const {
    return m_isDebug;
}

void Accelerometer::SetDebug(bool isDebug) {
    m_isDebug = isDebug;
}

std::array<double, 3> Accelerometer::ReadVoltages() const {
    if (m_isDebug){
        uint32_t voltageX = analogReadMilliVolts(m_xPin);
        uint32_t voltageY = analogReadMilliVolts(m_yPin);
        uint32_t voltageZ = analogReadMilliVolts(m_zPin);

        Serial.printf("X: %lu mV | Y: %lu mV | Z: %lu mV\n",
            (unsigned long)voltageX,
            (unsigned long)voltageY,
            (unsigned long)voltageZ);
    }

    return std::array<double, 3>{
        static_cast<double>(analogReadMilliVolts(m_xPin)),
        static_cast<double>(analogReadMilliVolts(m_yPin)),
        static_cast<double>(analogReadMilliVolts(m_zPin))
    };
}

std::array<double, 3> Accelerometer::VoltagesToGs(const std::array<double, 3>& voltages) const {
    double conversion = (m_mode == AccelerometerMode::LOW_ACCEL) 
        ? LOW_ACCEL_VOLTS_MV_PER_G : HIGH_ACCEL_VOLTS_MV_PER_G;
    
    return std::array<double, 3>{
        (static_cast<double>(voltages[0]) - ZERO_G_VOLTAGE_MV) / conversion,
        (static_cast<double>(voltages[1]) - ZERO_G_VOLTAGE_MV) / conversion,
        (static_cast<double>(voltages[2]) - ZERO_G_VOLTAGE_MV) / conversion
    };
}

std::array<double, 3> Accelerometer::GsToAccelerations(const std::array<double, 3>& gs) {
    return std::array<double, 3>{
        gs[0] * GRAVITY,
        gs[1] * GRAVITY,
        gs[2] * GRAVITY
    };
}

std::array<double, 3> Accelerometer::ApplyOffsets(const std::array<double, 3>& accelerations) const {
    return std::array<double, 3>{
        accelerations[0] - (m_mode == AccelerometerMode::LOW_ACCEL ? X_LOW_OFFSET : X_HIGH_OFFSET),
        accelerations[1] - (m_mode == AccelerometerMode::LOW_ACCEL ? Y_LOW_OFFSET : Y_HIGH_OFFSET),
        accelerations[2] - (m_mode == AccelerometerMode::LOW_ACCEL ? Z_LOW_OFFSET : Z_HIGH_OFFSET)
    };
}