#include <gtest/gtest.h>
#include "ActuSense/ConcreteSensors.h"
#include "ActuSense/Environment.h"

TEST(SensorTest, TemperatureSensorReading) {
    Environment env;
    TemperatureSensor sensor("TestTemp");
    
    // Initial reading might be 0, but update should bring it closer to env
    env.triggerHeatWave(10.0f); // target 35C
    sensor.update(env, 1.0f);
    
    auto reading = sensor.getReading();
    EXPECT_EQ(reading.size(), 1);
    EXPECT_GT(reading[0], 0.0f);
}

TEST(SensorTest, Calibration) {
    Environment env;
    TemperatureSensor sensor("TestTemp");
    
    // Force a known reading via calibration
    sensor.update(env, 0.1f);
    float current = sensor.getReading()[0];
    
    // We want the sensor to read exactly 100.0
    sensor.calibrate({100.0f});
    
    // After calibration, if env is same, it should be close to 100
    // Note: there is noise, so we check range
    sensor.update(env, 0.001f); // minimal time step to avoid drift
    EXPECT_NEAR(sensor.getReading()[0], 100.0f, 1.0f);
}

TEST(SensorTest, HealthStatus) {
    Environment env;
    TemperatureSensor sensor("TestTemp");
    
    EXPECT_TRUE(sensor.isHealthy());
    sensor.setHealthy(false);
    EXPECT_FALSE(sensor.isHealthy());
    
    sensor.update(env, 1.0f);
    EXPECT_EQ(sensor.getReading()[0], -999.0f);
}
