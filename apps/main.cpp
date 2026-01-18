#include <iostream>
#include <thread>
#include <chrono>
#include "ActuSense/Environment.h"
#include "ActuSense/ConcreteSensors.h"
#include "ActuSense/TestFramework.h"
#include "ActuSense/Visualization.h"
#include "ActuSense/DataLogger.h"
#include "ActuSense/SensorFactory.h"

int main() {
    std::cout << "Starting Sensor Simulation System..." << std::endl;

    Environment env;
    TestFramework framework(env);
    DataLogger logger("sensor_data.csv");

    // Initialize Factory and Registry
    auto& factory = ActuSense::SensorFactory::getInstance();
    
    // Create Sensors via Factory
    auto tempSensor = factory.create("temperature", "Temp Sensor A");
    auto pressureSensor = factory.create("pressure", "Pressure Sensor B");
    auto accelSensor = factory.create("accelerometer", "Accel Sensor C");
    auto proxSensor = factory.create("proximity", "Proximity Sensor D");

    if (tempSensor) framework.addSensor(tempSensor);
    if (pressureSensor) framework.addSensor(pressureSensor);
    if (accelSensor) framework.addSensor(accelSensor);
    if (proxSensor) framework.addSensor(proxSensor);

    Visualization viz;

    // Simulation Loop
    auto lastTime = std::chrono::high_resolution_clock::now();
    
    while (true) {
        auto currentTime = std::chrono::high_resolution_clock::now();
        float deltaTime = std::chrono::duration<float>(currentTime - lastTime).count();
        lastTime = currentTime;

        // Handle Input (if SFML) or simple console input logic could go here
        if (viz.isOpen()) {
            viz.processEvents();
            
            // Simple key checks for interaction (using SFML directly here for simplicity)
            #ifdef SFML_FOUND
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::H)) {
                env.triggerHeatWave(10.0f * deltaTime); // Hold to heat
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
                env.triggerShock(1.0f); // Tap for shock
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::C)) {
                framework.runCalibrationRoutine();
            }
            #endif
        } else {
            // Console mode exit condition?
            // For now, just run forever or until Ctrl+C
        }

        // Update
        env.update(deltaTime);
        framework.update(deltaTime);

        // Logging
        logger.logHeader(framework.getSensors());
        
        static float totalTime = 0.0f;
        totalTime += deltaTime;
        logger.logData(totalTime, framework.getSensors());

        // Render
        viz.render(env, framework);

        // Cap frame rate if no window
        if (!viz.isOpen()) {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    }

    return 0;
}
