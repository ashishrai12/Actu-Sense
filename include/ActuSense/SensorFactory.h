#pragma once
#include "ActuSense/Sensor.h"
#include <memory>
#include <string>
#include <map>
#include <functional>

namespace ActuSense {

class SensorFactory {
public:
    using CreatorFunc = std::function<std::shared_ptr<Sensor>(const std::string&)>;

    static SensorFactory& getInstance() {
        static SensorFactory instance;
        return instance;
    }

    void registerSensor(const std::string& type, CreatorFunc creator) {
        creators[type] = creator;
    }

    std::shared_ptr<Sensor> create(const std::string& type, const std::string& name) {
        auto it = creators.find(type);
        if (it != creators.end()) {
            return it->second(name);
        }
        return nullptr;
    }

private:
    SensorFactory();
    std::map<std::string, CreatorFunc> creators;
};

} // namespace ActuSense
