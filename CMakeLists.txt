cmake_minimum_required(VERSION 3.10)
project(SensorSimulation)

set(CMAKE_CXX_STANDARD 17)

# Find SFML
find_package(SFML 2.5 COMPONENTS graphics window system)

if(NOT SFML_FOUND)
    message(WARNING "SFML not found. Please install SFML or set SFML_DIR to the directory containing SFMLConfig.cmake")
    # Fallback or instructions could go here, but for now we assume the user will provide it.
endif()

include_directories(${SFML_INCLUDE_DIR})

file(GLOB SOURCES "src/*.cpp")
file(GLOB HEADERS "src/*.h")

add_executable(SensorSimulation ${SOURCES} ${HEADERS})

if(SFML_FOUND)
    target_link_libraries(SensorSimulation ${SFML_LIBRARIES})
    add_definitions(-DSFML_FOUND)
else()
    message(STATUS "Building without SFML linking (will fail if code uses SFML)")
endif()
