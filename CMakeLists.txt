cmake_minimum_required(VERSION 3.14)
project(ActuSense VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Options
option(BUILD_TESTS "Build unit tests" ON)
option(ENABLE_VISUALIZATION "Enable SFML visualization" ON)

# Find SFML
if(ENABLE_VISUALIZATION)
    find_package(SFML 2.5 COMPONENTS graphics window system)
    if(SFML_FOUND)
        message(STATUS "SFML found, visualization enabled.")
        add_definitions(-DSFML_FOUND)
    else()
        message(WARNING "SFML not found. Visualization will be disabled.")
    endif()
endif()

# Core Library
set(LIB_SOURCES
    src/Sensor.cpp
    src/ConcreteSensors.cpp
    src/Environment.cpp
    src/TestFramework.cpp
    src/Visualization.cpp
    src/DataLogger.cpp
)

add_library(ActuSenseLib ${LIB_SOURCES})

target_include_directories(ActuSenseLib PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

if(SFML_FOUND)
    target_link_libraries(ActuSenseLib PUBLIC sfml-graphics sfml-window sfml-system)
endif()

# Main Application
add_executable(ActuSenseApp apps/main.cpp)
target_link_libraries(ActuSenseApp PRIVATE ActuSenseLib)

# Testing
if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()
