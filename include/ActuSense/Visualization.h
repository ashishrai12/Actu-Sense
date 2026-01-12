#pragma once
#ifdef SFML_FOUND
#include <SFML/Graphics.hpp>
#endif
#include "ActuSense/Environment.h"
#include "ActuSense/TestFramework.h"
#include <vector>
#include <deque>

class Visualization {
public:
    Visualization();
    bool isOpen() const;
    void processEvents();
    void render(const Environment& env, const TestFramework& framework);

private:
#ifdef SFML_FOUND
    sf::RenderWindow window;
    sf::Font font;
    
    // History for graphs
    std::map<std::string, std::deque<float>> sensorHistory;
    const size_t maxHistory = 200;

    void drawGraph(const std::string& title, const std::deque<float>& data, 
                   float minVal, float maxVal, 
                   float x, float y, float w, float h, sf::Color color);
    
    void drawEnvironment(const Environment& env);
    void drawMetrics(const TestFramework& framework);
#endif
};
