#pragma once

#include <cstdint>
#include <array>

enum class AccelerometerMode {
    LOW_ACCEL,
    HIGH_ACCEL
};

class Accelerometer {
private:
    uint8_t m_xPin;
    uint8_t m_yPin;
    uint8_t m_zPin;
    uint8_t m_gselectPin;

    double m_x;
    double m_y;
    double m_z;

    AccelerometerMode m_mode;
    bool m_isDebug;
public:
    Accelerometer(uint8_t xPin, uint8_t yPin, uint8_t zPin, uint8_t gselectPin, 
        AccelerometerMode mode);
    Accelerometer(uint8_t xPin, uint8_t yPin, uint8_t zPin, uint8_t gselectPin, 
        AccelerometerMode mode, bool isDebug);

    AccelerometerMode GetMode() const;
    void SetMode(AccelerometerMode mode);
public:
    double GetX() const;
    double GetY() const;
    double GetZ() const;

    // in order of 'x, y, z'
    std::array<double, 3> GetAccelerations();
    double GetAcclerationMagnitude();

    bool IsDebug() const;
    void SetDebug(bool isDebug);
private:
    void ReadVoltages();

    // MMA7361 accelerometer conversions
    constexpr static double LOW_ACCEL_VOLTS_MV_PER_G = 800;
    constexpr static double HIGH_ACCEL_VOLTS_MV_PER_G = 206;
    constexpr static double ZERO_G_X_VOLTAGE_MV = 1650;
    constexpr static double ZERO_G_Y_VOLTAGE_MV = 1650;
    constexpr static double ZERO_G_Z_VOLTAGE_MV = 1650;
    void VoltagesToGs(const std::array<uint32_t, 3>& voltages);

    // converts g's to m/s^2
    constexpr static double GRAVITY = 9.81;
    void GsToAccelerations();

    // low acceleration calibration offsets
    constexpr static double X_LOW_OFFSET = -0.0020;
    constexpr static double Y_LOW_OFFSET = 1.8171;
    constexpr static double Z_LOW_OFFSET = -3.0934;
    // high acceleration calibration offsets
    constexpr static double X_HIGH_OFFSET = 2.0303;
    constexpr static double Y_HIGH_OFFSET = 3.6834;
    constexpr static double Z_HIGH_OFFSET = -2.6814;
    void ApplyOffsets();
};