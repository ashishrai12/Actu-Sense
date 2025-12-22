#include <iostream>
#include <thread>
#include <chrono>
#include "Environment.h"
#include "ConcreteSensors.h"
#include "TestFramework.h"
#include "Visualization.h"

int main() {
    std::cout << "Starting Sensor Simulation System..." << std::endl;

    Environment env;
    TestFramework framework(env);

    // Create Sensors
    auto tempSensor = std::make_shared<TemperatureSensor>("Temp Sensor A");
    auto pressureSensor = std::make_shared<PressureSensor>("Pressure Sensor B");
    auto accelSensor = std::make_shared<Accelerometer>("Accel Sensor C");
    auto proxSensor = std::make_shared<ProximitySensor>("Proximity Sensor D");

    framework.addSensor(tempSensor);
    framework.addSensor(pressureSensor);
    framework.addSensor(accelSensor);
    framework.addSensor(proxSensor);

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

        // Render
        viz.render(env, framework);

        // Cap frame rate if no window
        if (!viz.isOpen()) {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    }

    return 0;
}
