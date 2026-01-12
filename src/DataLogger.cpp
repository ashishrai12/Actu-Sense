#include "ActuSense/DataLogger.h"
#include <iomanip>

DataLogger::DataLogger(const std::string& filename) : headerWritten(false) {
    outFile.open(filename);
}

DataLogger::~DataLogger() {
    if (outFile.is_open()) {
        outFile.close();
    }
}

void DataLogger::logHeader(const std::vector<std::shared_ptr<Sensor>>& sensors) {
    if (headerWritten || !outFile.is_open()) return;

    outFile << "Timestamp,";
    for (size_t i = 0; i < sensors.size(); ++i) {
        outFile << sensors[i]->getName();
        if (i < sensors.size() - 1) outFile << ",";
    }
    outFile << "\n";
    headerWritten = true;
}

void DataLogger::logData(float timestamp, const std::vector<std::shared_ptr<Sensor>>& sensors) {
    if (!outFile.is_open()) return;

    outFile << std::fixed << std::setprecision(3) << timestamp << ",";
    for (size_t i = 0; i < sensors.size(); ++i) {
        auto readings = sensors[i]->getReading();
        // Just log the first component for simplicity in CSV, or expand to all
        outFile << readings[0]; 
        if (i < sensors.size() - 1) outFile << ",";
    }
    outFile << "\n";
}
