#pragma once
#include <vector>
#include <memory>
#include <map>
#include "ActuSense/Sensor.h"
#include "ActuSense/Environment.h"

struct SensorMetrics {
    float minVal = 1e9;
    float maxVal = -1e9;
    float avgVal = 0;
    int sampleCount = 0;
    float lastResponseTime = 0; // Time to reach 90% of a step change (simplified)
};

class TestFramework {
public:
    TestFramework(Environment& env);
    
    void addSensor(std::shared_ptr<Sensor> sensor);
    void update(float deltaTime);
    
    const std::vector<std::shared_ptr<Sensor>>& getSensors() const;
    const std::map<std::string, SensorMetrics>& getMetrics() const;

    // Simple test routines
    void runCalibrationRoutine();
    void runStressTest();

private:
    Environment& env;
    std::vector<std::shared_ptr<Sensor>> sensors;
    std::map<std::string, SensorMetrics> metrics;
    
    void updateMetrics(std::shared_ptr<Sensor> sensor);
};
