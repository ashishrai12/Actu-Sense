#include "Environment.h"
#include <algorithm>
#include <iostream>

Environment::Environment() 
    : temperature(25.0f), pressure(101325.0f), vibration(0.0f), proximity(10.0f),
      targetTemperature(25.0f), targetPressure(101325.0f), timeSinceLastShock(100.0f) {
    
    std::random_device rd;
    rng = std::mt19937(rd());
    tempFluctuation = std::normal_distribution<float>(0.0f, 0.05f); // Small fluctuations
    pressureFluctuation = std::normal_distribution<float>(0.0f, 10.0f);
    vibrationNoise = std::normal_distribution<float>(0.0f, 0.01f);
}

void Environment::update(float deltaTime) {
    // Drift towards target values
    float tempDiff = targetTemperature - temperature;
    temperature += tempDiff * 0.5f * deltaTime;
    
    float pressureDiff = targetPressure - pressure;
    pressure += pressureDiff * 0.5f * deltaTime;

    // Add random noise
    temperature += tempFluctuation(rng);
    pressure += pressureFluctuation(rng);

    // Vibration decay
    if (vibration > 0.0f) {
        vibration -= vibration * 2.0f * deltaTime; // Decay
        if (vibration < 0.0f) vibration = 0.0f;
    }
    // Base vibration noise
    float noise = vibrationNoise(rng);
    if (vibration + noise > 0) vibration += noise;

    timeSinceLastShock += deltaTime;
    
    // Slowly return targets to baseline
    targetTemperature += (25.0f - targetTemperature) * 0.05f * deltaTime;
    targetPressure += (101325.0f - targetPressure) * 0.05f * deltaTime;
}

float Environment::getTemperature() const { return temperature; }
float Environment::getPressure() const { return pressure; }
float Environment::getVibration() const { return vibration; }
float Environment::getProximity() const { return proximity; }

void Environment::triggerShock(float magnitude) {
    vibration += magnitude;
    timeSinceLastShock = 0.0f;
}

void Environment::triggerHeatWave(float tempIncrease) {
    targetTemperature += tempIncrease;
}

void Environment::triggerPressureSpike(float pressureIncrease) {
    targetPressure += pressureIncrease;
}

void Environment::setProximity(float distance) {
    proximity = distance;
}
