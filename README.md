# ActuSense: Sensor Simulation & Testing Framework

ActuSense is a professional C++ framework for simulating sensor environments, testing sensor health, and visualizing real-time data. It is designed with modularity and extensibility in mind, making it suitable for both educational purposes and prototyping industrial sensor networks.

## ✨ Features

- **Multi-Sensor Simulation**: Temperature, Pressure, 3-Axis Accelerometers, and Proximity sensors.
- **Dynamic Environment**: Simulate thermal drift, pressure spikes, mechanical shocks, and proximity changes.
- **Real-Time Visualization**: Adaptive graphical interface using SFML with historical data tracking.
- **Automated Data Logging**: Export sensor readings to CSV for offline analysis.
- **Calibration Framework**: Built-in routines for sensor offset calibration.
- **Unit Testing**: Comprehensive test suite using GoogleTest.
- **Containerized**: Full Docker support for reproducible builds and CI/CD.

## 📂 Project Structure

```text
ActuSense/
├── apps/               # Application entry points
├── include/ActuSense/  # Public headers
├── src/                # Implementation files
├── tests/              # Unit tests (GoogleTest)
├── Dockerfile          # Container configuration
└── CMakeLists.txt      # Build system configuration
```

## 🚀 Getting Started

### Prerequisites

- **C++17 Compiler** (GCC 9+, Clang 10+, or MSVC 2019+)
- **CMake 3.14+**
- **SFML 2.5** (Optional, for GUI)

### Build & Run

1. **Configure and Build**:
   ```bash
   cmake -S . -B build -DENABLE_VISUALIZATION=ON
   cmake --build build --config Release
   ```

2. **Run the Application**:
   ```bash
   ./build/apps/ActuSenseApp
   ```

3. **Run Tests**:
   ```bash
   cd build
   ctest --output-on-failure
   ```

### Using Docker

Build and run without locally installing dependencies:

```bash
docker build -t actusense .
docker run -it actusense
```

## 📊 Data Analysis

The application automatically generates `sensor_data.csv` in the execution directory. You can import this into Excel, MATLAB, or Python for further analysis.

## 🛠️ Controls (in GUI mode)

- **[H]**: Trigger Heat Wave (Hold)
- **[S]**: Trigger Mechanical Shock (Tap)
- **[C]**: Run Calibration Routine
- **[ESC]**: Exit

## 📄 License

This project is licensed under the MIT License - see the LICENSE file for details.
