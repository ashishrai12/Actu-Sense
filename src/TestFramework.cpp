#include "TestFramework.h"
#include <iostream>
#include <cmath>

TestFramework::TestFramework(Environment& env) : env(env) {}

void TestFramework::addSensor(std::shared_ptr<Sensor> sensor) {
    sensors.push_back(sensor);
    metrics[sensor->getName()] = SensorMetrics();
}

void TestFramework::update(float deltaTime) {
    for (auto& sensor : sensors) {
        sensor->update(env, deltaTime);
        updateMetrics(sensor);
    }
}

void TestFramework::updateMetrics(std::shared_ptr<Sensor> sensor) {
    auto& m = metrics[sensor->getName()];
    auto reading = sensor->getReading();
    
    // Just track the first component for metrics simplicity
    float val = reading[0];
    
    if (val < m.minVal) m.minVal = val;
    if (val > m.maxVal) m.maxVal = val;
    
    // Running average
    m.avgVal = (m.avgVal * m.sampleCount + val) / (m.sampleCount + 1);
    m.sampleCount++;
}

const std::vector<std::shared_ptr<Sensor>>& TestFramework::getSensors() const {
    return sensors;
}

const std::map<std::string, SensorMetrics>& TestFramework::getMetrics() const {
    return metrics;
}

void TestFramework::runCalibrationRoutine() {
    std::cout << "Running Calibration Routine..." << std::endl;
    // In a real system, we would set the environment to a known state
    // and then tell the sensors to calibrate.
    // For simulation, we'll just pretend we set the environment to 25C, 101325Pa, etc.
    
    // 1. Stabilize environment (instant set for sim)
    // We can't easily force the environment to a specific value instantly without adding methods to Environment
    // But let's assume we are at "standard conditions"
    
    for (auto& sensor : sensors) {
        if (sensor->getType() == SensorType::Temperature) {
            sensor->calibrate({25.0f});
        } else if (sensor->getType() == SensorType::Pressure) {
            sensor->calibrate({101325.0f});
        } else if (sensor->getType() == SensorType::Accelerometer) {
            sensor->calibrate({0.0f, 9.81f, 0.0f});
        }
    }
    std::cout << "Calibration Complete." << std::endl;
}

void TestFramework::runStressTest() {
    std::cout << "Running Stress Test..." << std::endl;
    env.triggerShock(5.0f); // 5G shock
    env.triggerHeatWave(50.0f); // Sudden heat
}
