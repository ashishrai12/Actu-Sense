#include "ActuSense/SensorFactory.h"
#include "ActuSense/ConcreteSensors.h"

namespace ActuSense {

SensorFactory::SensorFactory() {
    // Register default sensor types
    registerSensor("temperature", [](const std::string& name) {
        return std::make_shared<TemperatureSensor>(name);
    });
    
    registerSensor("pressure", [](const std::string& name) {
        return std::make_shared<PressureSensor>(name);
    });
    
    registerSensor("accelerometer", [](const std::string& name) {
        return std::make_shared<Accelerometer>(name);
    });
    
    registerSensor("proximity", [](const std::string& name) {
        return std::make_shared<ProximitySensor>(name);
    });
}

} // namespace ActuSense
