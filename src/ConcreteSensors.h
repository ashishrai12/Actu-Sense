#pragma once
#include "Sensor.h"
#include <cmath>

class TemperatureSensor : public Sensor {
public:
    TemperatureSensor(std::string name);
    void update(const Environment& env, float deltaTime) override;
    std::vector<float> getReading() const override;
    std::string getReadingString() const override;
private:
    float thermalMass; // Simulates lag
};

class PressureSensor : public Sensor {
public:
    PressureSensor(std::string name);
    void update(const Environment& env, float deltaTime) override;
    std::vector<float> getReading() const override;
    std::string getReadingString() const override;
};

class Accelerometer : public Sensor {
public:
    Accelerometer(std::string name);
    void update(const Environment& env, float deltaTime) override;
    std::vector<float> getReading() const override;
    std::string getReadingString() const override;
};

class ProximitySensor : public Sensor {
public:
    ProximitySensor(std::string name);
    void update(const Environment& env, float deltaTime) override;
    std::vector<float> getReading() const override;
    std::string getReadingString() const override;
};
