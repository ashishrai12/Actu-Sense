#include <gtest/gtest.h>
#include "ActuSense/SensorFactory.h"

TEST(SensorFactoryTest, CreateValidSensors) {
    auto& factory = ActuSense::SensorFactory::getInstance();
    
    auto temp = factory.create("temperature", "T1");
    auto press = factory.create("pressure", "P1");
    auto accel = factory.create("accelerometer", "A1");
    auto prox = factory.create("proximity", "X1");
    
    EXPECT_NE(temp, nullptr);
    EXPECT_NE(press, nullptr);
    EXPECT_NE(accel, nullptr);
    EXPECT_NE(prox, nullptr);
    
    EXPECT_EQ(temp->getName(), "T1");
    EXPECT_EQ(press->getName(), "P1");
}

TEST(SensorFactoryTest, CreateInvalidSensor) {
    auto& factory = ActuSense::SensorFactory::getInstance();
    auto invalid = factory.create("quantum_flux", "Q1");
    EXPECT_EQ(invalid, nullptr);
}
