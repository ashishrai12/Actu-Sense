#pragma once
#include <random>
#include <chrono>

class Environment {
public:
    Environment();

    void update(float deltaTime);
    
    // Getters
    float getTemperature() const;
    float getPressure() const;
    float getVibration() const; // Magnitude of vibration
    float getProximity() const; // Distance to nearest object

    // Event triggers
    void triggerShock(float magnitude);
    void triggerHeatWave(float tempIncrease);
    void triggerPressureSpike(float pressureIncrease);
    void setProximity(float distance);

private:
    float temperature; // Celsius
    float pressure;    // Pascal
    float vibration;   // G-force
    float proximity;   // Meters

    // Target values for smooth transitions
    float targetTemperature;
    float targetPressure;

    // Random number generation
    std::mt19937 rng;
    std::normal_distribution<float> tempFluctuation;
    std::normal_distribution<float> pressureFluctuation;
    std::normal_distribution<float> vibrationNoise;
    
    float timeSinceLastShock;
};
