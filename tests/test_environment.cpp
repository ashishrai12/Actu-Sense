#include <gtest/gtest.h>
#include "ActuSense/Environment.h"

TEST(EnvironmentTest, DefaultValues) {
    Environment env;
    EXPECT_NEAR(env.getTemperature(), 25.0f, 1.0f);
    EXPECT_NEAR(env.getPressure(), 101325.0f, 100.0f);
    EXPECT_EQ(env.getVibration(), 0.0f);
}

TEST(EnvironmentTest, Interaction) {
    Environment env;
    
    env.triggerHeatWave(20.0f);
    env.update(1.0f);
    EXPECT_GT(env.getTemperature(), 25.0f);
    
    env.triggerShock(10.0f);
    EXPECT_GT(env.getVibration(), 0.0f);
    
    env.update(10.0f); // vibration should decay
    EXPECT_LT(env.getVibration(), 10.0f);
}

TEST(EnvironmentTest, Proximity) {
    Environment env;
    env.setProximity(5.5f);
    EXPECT_FLOAT_EQ(env.getProximity(), 5.5f);
}
