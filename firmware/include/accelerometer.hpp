#pragma once

#include <Arduino.h>

#include <array>
#include <cstdint>

enum class AccelerometerMode {
    LOW_ACCEL,
    HIGH_ACCEL
};

class Accelerometer {
private:
    const uint8_t m_xPin;
    const uint8_t m_yPin;
    const uint8_t m_zPin;
    const uint8_t m_gselectPin;

    AccelerometerMode m_mode;
private:
    static constexpr auto ADC_ATTENUATION = ADC_11db;
public:
    Accelerometer(const uint8_t xPin, const uint8_t yPin, const uint8_t zPin, const uint8_t gselectPin, 
        const AccelerometerMode mode);

    AccelerometerMode GetMode() const;
    void SetMode(AccelerometerMode mode);
public:
    // in order of 'x, y, z'
    std::array<double, 3> GetAccelerations() const;
    double GetAcclerationMagnitude() const;
private:
    std::array<double, 3> ReadVoltages() const;

    // constants from MMA7361 datasheet
    // MMA7361 accelerometer conversions
    static constexpr double LOW_ACCEL_VOLTS_MV_PER_G = 800;
    static constexpr double HIGH_ACCEL_VOLTS_MV_PER_G = 206;

    // zero-g voltage in millivolts (note: these values could (should) be different for each axis; however, instead
    // of calibrating the zero-g voltage for each axis, we will instead do all the calibration at the end in m/s^2)
    static constexpr double ZERO_G_VOLTAGE_MV = 1650;
    std::array<double, 3> VoltagesToGs(const std::array<double, 3>& voltages) const;

    // converts g's to m/s^2
    static constexpr double GRAVITY = 9.81;
    static std::array<double, 3> GsToAccelerations(const std::array<double, 3>& gs);

    // low acceleration calibration offsets
    static constexpr double X_LOW_OFFSET = -0.0020;
    static constexpr double Y_LOW_OFFSET = 1.8171;
    static constexpr double Z_LOW_OFFSET = -3.0934;
    // high acceleration calibration offsets
    static constexpr double X_HIGH_OFFSET = 2.0303;
    static constexpr double Y_HIGH_OFFSET = 3.6834;
    static constexpr double Z_HIGH_OFFSET = -2.6814;
    std::array<double, 3> ApplyOffsets(const std::array<double, 3>& accelerations) const;
};