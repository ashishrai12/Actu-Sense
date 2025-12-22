# Sensor Simulation System

## Overview
This is a C++ simulation of a sensor actuation and testing system. It simulates:
- **Environment**: Temperature, Pressure, Vibration, Proximity.
- **Sensors**: Temperature, Pressure, Accelerometer, Proximity sensors with noise and lag.
- **Testing**: Calibration routines and stress tests.
- **Visualization**: Real-time graphs using SFML (or console fallback).

## Prerequisites
- C++ Compiler (GCC, Clang, or MSVC) supporting C++17.
- CMake (optional, but recommended).
- SFML 2.5+ (optional, for graphical visualization).

## Build Instructions

### Using CMake (Recommended)
1. Create a build directory:
   ```bash
   mkdir build
   cd build
   ```
2. Configure the project:
   ```bash
   cmake ..
   ```
   *Note: If SFML is not found, the project will automatically configure in Console-only mode.*

3. Build:
   ```bash
   cmake --build .
   ```

4. Run:
   ```bash
   ./SensorSimulation
   # or on Windows:
   .\Debug\SensorSimulation.exe
   ```

### Manual Compilation (g++)
If you don't have CMake but have g++, you can compile directly.
**Console Mode (No SFML):**
```bash
g++ -std=c++17 src/*.cpp -o SensorSim
./SensorSim
```

**With SFML (if installed):**
```bash
g++ -std=c++17 src/*.cpp -o SensorSim -DSFML_FOUND -lsfml-graphics -lsfml-window -lsfml-system
./SensorSim
```
