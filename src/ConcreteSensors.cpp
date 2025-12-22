#include "ConcreteSensors.h"
#include <sstream>
#include <iomanip>

// --- TemperatureSensor ---
TemperatureSensor::TemperatureSensor(std::string name) 
    : Sensor(name, SensorType::Temperature), thermalMass(0.0f) {
    currentReading = {0.0f};
    calibrationOffsets = {0.0f};
}

void TemperatureSensor::update(const Environment& env, float deltaTime) {
    if (!healthy) {
        currentReading[0] = -999.0f; // Error code
        return;
    }
    
    float envTemp = env.getTemperature();
    // Simulate thermal lag
    float diff = envTemp - currentReading[0];
    currentReading[0] += diff * 2.0f * deltaTime; 
    
    // Add noise
    currentReading[0] += generateNoise(0.1f);
    
    // Apply calibration
    currentReading[0] += calibrationOffsets[0];
}

std::vector<float> TemperatureSensor::getReading() const { return currentReading; }

std::string TemperatureSensor::getReadingString() const {
    std::stringstream ss;
    ss << std::fixed << std::setprecision(2) << currentReading[0] << " C";
    return ss.str();
}

// --- PressureSensor ---
PressureSensor::PressureSensor(std::string name) 
    : Sensor(name, SensorType::Pressure) {
    currentReading = {0.0f};
    calibrationOffsets = {0.0f};
}

void PressureSensor::update(const Environment& env, float deltaTime) {
    if (!healthy) return;

    float envPressure = env.getPressure();
    currentReading[0] = envPressure + generateNoise(50.0f); // +/- 50 Pa noise
    currentReading[0] += calibrationOffsets[0];
}

std::vector<float> PressureSensor::getReading() const { return currentReading; }

std::string PressureSensor::getReadingString() const {
    std::stringstream ss;
    ss << std::fixed << std::setprecision(0) << currentReading[0] << " Pa";
    return ss.str();
}

// --- Accelerometer ---
Accelerometer::Accelerometer(std::string name) 
    : Sensor(name, SensorType::Accelerometer) {
    currentReading = {0.0f, 0.0f, 0.0f}; // X, Y, Z
    calibrationOffsets = {0.0f, 0.0f, 0.0f};
}

void Accelerometer::update(const Environment& env, float deltaTime) {
    if (!healthy) return;

    // Base gravity
    float x = 0.0f;
    float y = 9.81f;
    float z = 0.0f;

    // Add vibration from environment (random direction)
    float vib = env.getVibration();
    if (vib > 0) {
        x += generateNoise(vib * 5.0f);
        y += generateNoise(vib * 5.0f);
        z += generateNoise(vib * 5.0f);
    }

    currentReading[0] = x + calibrationOffsets[0];
    currentReading[1] = y + calibrationOffsets[1];
    currentReading[2] = z + calibrationOffsets[2];
}

std::vector<float> Accelerometer::getReading() const { return currentReading; }

std::string Accelerometer::getReadingString() const {
    std::stringstream ss;
    ss << std::fixed << std::setprecision(2) 
       << "X:" << currentReading[0] << " Y:" << currentReading[1] << " Z:" << currentReading[2];
    return ss.str();
}

// --- ProximitySensor ---
ProximitySensor::ProximitySensor(std::string name) 
    : Sensor(name, SensorType::Proximity) {
    currentReading = {0.0f};
    calibrationOffsets = {0.0f};
}

void ProximitySensor::update(const Environment& env, float deltaTime) {
    if (!healthy) return;

    float dist = env.getProximity();
    // Add some noise
    currentReading[0] = dist + generateNoise(0.05f);
    if (currentReading[0] < 0) currentReading[0] = 0;
    
    currentReading[0] += calibrationOffsets[0];
}

std::vector<float> ProximitySensor::getReading() const { return currentReading; }

std::string ProximitySensor::getReadingString() const {
    std::stringstream ss;
    ss << std::fixed << std::setprecision(2) << currentReading[0] << " m";
    return ss.str();
}
