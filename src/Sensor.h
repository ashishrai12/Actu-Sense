#pragma once
#include <string>
#include <vector>
#include "Environment.h"

enum class SensorType {
    Temperature,
    Pressure,
    Accelerometer,
    Proximity
};

class Sensor {
public:
    Sensor(std::string name, SensorType type);
    virtual ~Sensor() = default;

    // Reads the sensor value based on the environment
    virtual void update(const Environment& env, float deltaTime) = 0;
    
    // Get the latest reading
    virtual std::vector<float> getReading() const = 0;
    
    // Get formatted string of reading
    virtual std::string getReadingString() const = 0;

    std::string getName() const { return name; }
    SensorType getType() const { return type; }

    // Calibration
    void calibrate(const std::vector<float>& knownValues);
    std::vector<float> getCalibrationOffsets() const { return calibrationOffsets; }

    // Status
    bool isHealthy() const { return healthy; }
    void setHealthy(bool status) { healthy = status; }

protected:
    std::string name;
    SensorType type;
    std::vector<float> currentReading;
    std::vector<float> calibrationOffsets;
    bool healthy;
    
    // Helper for noise
    float generateNoise(float intensity);
};
