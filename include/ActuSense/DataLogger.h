#pragma once
#include <fstream>
#include <string>
#include <vector>
#include <memory>
#include "ActuSense/Sensor.h"

class DataLogger {
public:
    DataLogger(const std::string& filename);
    ~DataLogger();

    void logHeader(const std::vector<std::shared_ptr<Sensor>>& sensors);
    void logData(float timestamp, const std::vector<std::shared_ptr<Sensor>>& sensors);

private:
    std::ofstream outFile;
    bool headerWritten;
};
