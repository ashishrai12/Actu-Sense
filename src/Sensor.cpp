#include "ActuSense/Sensor.h"
#include <random>
#include <sstream>
#include <iomanip>

Sensor::Sensor(std::string name, SensorType type) 
    : name(name), type(type), healthy(true) {
    // Initialize offsets based on type dimension (scalar vs vector)
    // For simplicity, we'll resize in derived classes or assume 1D for now, 
    // but Accelerometer is 3D.
}

void Sensor::calibrate(const std::vector<float>& knownValues) {
    if (currentReading.size() != knownValues.size()) return;
    
    calibrationOffsets.resize(currentReading.size());
    for (size_t i = 0; i < currentReading.size(); ++i) {
        // Simple offset calibration: Offset = Known - (Reading_raw)
        // But here currentReading includes previous offset. 
        // Let's assume currentReading is the "measured" value.
        // We want Measured + NewOffset = Known.
        // So NewOffset = Known - (Measured - OldOffset).
        // Or simpler: just reset offset so that (Raw + Offset) = Known.
        // We don't store Raw separately here, which is a simplification.
        // Let's just adjust the offset by the difference.
        float diff = knownValues[i] - currentReading[i];
        calibrationOffsets[i] += diff;
    }
}

float Sensor::generateNoise(float intensity) {
    static std::mt19937 rng(std::random_device{}());
    std::normal_distribution<float> dist(0.0f, intensity);
    return dist(rng);
}
