#include "ActuSense/Visualization.h"
#include <iostream>
#include <iomanip>
#include <sstream>

Visualization::Visualization() {
#ifdef SFML_FOUND
    window.create(sf::VideoMode(1200, 800), "Sensor Simulation");
    window.setFramerateLimit(60);
    
    // Try to load a font
    if (!font.loadFromFile("C:/Windows/Fonts/arial.ttf")) {
        std::cerr << "Failed to load font. Text will not be displayed." << std::endl;
    }
#endif
}

bool Visualization::isOpen() const {
#ifdef SFML_FOUND
    return window.isOpen();
#else
    return false;
#endif
}

void Visualization::processEvents() {
#ifdef SFML_FOUND
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
    }
#endif
}

void Visualization::render(const Environment& env, const TestFramework& framework) {
#ifdef SFML_FOUND
    window.clear(sf::Color(30, 30, 30));

    // Update history
    for (const auto& sensor : framework.getSensors()) {
        auto& history = sensorHistory[sensor->getName()];
        history.push_back(sensor->getReading()[0]); // Graph 1st component
        if (history.size() > maxHistory) history.pop_front();
    }

    // Draw Environment Status
    drawEnvironment(env);

    // Draw Graphs
    float yPos = 200.0f;
    for (const auto& sensor : framework.getSensors()) {
        auto& history = sensorHistory[sensor->getName()];
        drawGraph(sensor->getName() + ": " + sensor->getReadingString(), 
                  history, -50, 150, // Approximate range, dynamic would be better
                  50.0f, yPos, 500.0f, 100.0f, sf::Color::Green);
        yPos += 120.0f;
    }

    // Draw Metrics
    drawMetrics(framework);

    window.display();
#else
    // Console fallback
    std::cout << "--- Environment ---" << std::endl;
    std::cout << "Temp: " << env.getTemperature() << " C" << std::endl;
    std::cout << "Pressure: " << env.getPressure() << " Pa" << std::endl;
    std::cout << "Vibration: " << env.getVibration() << " G" << std::endl;
    
    for (const auto& sensor : framework.getSensors()) {
        std::cout << sensor->getName() << ": " << sensor->getReadingString() << std::endl;
    }
    std::cout << "-------------------" << std::endl;
#endif
}

#ifdef SFML_FOUND
void Visualization::drawGraph(const std::string& title, const std::deque<float>& data, 
                              float minVal, float maxVal, 
                              float x, float y, float w, float h, sf::Color color) {
    
    // Background
    sf::RectangleShape bg(sf::Vector2f(w, h));
    bg.setPosition(x, y);
    bg.setFillColor(sf::Color(50, 50, 50));
    bg.setOutlineColor(sf::Color::White);
    bg.setOutlineThickness(1.0f);
    window.draw(bg);

    // Title
    sf::Text text(title, font, 14);
    text.setPosition(x, y - 20);
    text.setFillColor(sf::Color::White);
    window.draw(text);

    if (data.empty()) return;

    // Plot lines
    sf::VertexArray lines(sf::LinesStrip, data.size());
    float xStep = w / (maxHistory - 1);
    
    // Auto-scale if needed, but using fixed for now for stability
    float range = maxVal - minVal;
    if (range == 0) range = 1.0f;

    for (size_t i = 0; i < data.size(); ++i) {
        float val = data[i];
        // Clamp
        if (val < minVal) val = minVal;
        if (val > maxVal) val = maxVal;

        float normalized = (val - minVal) / range;
        float py = y + h - (normalized * h);
        float px = x + (i * xStep);
        
        lines[i].position = sf::Vector2f(px, py);
        lines[i].color = color;
    }
    window.draw(lines);
}

void Visualization::drawEnvironment(const Environment& env) {
    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(16);
    text.setFillColor(sf::Color::Yellow);
    text.setPosition(50, 20);

    std::stringstream ss;
    ss << "Environment Simulation:\n"
       << "Temperature: " << std::fixed << std::setprecision(2) << env.getTemperature() << " C\n"
       << "Pressure: " << std::fixed << std::setprecision(0) << env.getPressure() << " Pa\n"
       << "Vibration: " << std::fixed << std::setprecision(3) << env.getVibration() << " G\n"
       << "Proximity: " << std::fixed << std::setprecision(2) << env.getProximity() << " m";
    
    text.setString(ss.str());
    window.draw(text);
}

void Visualization::drawMetrics(const TestFramework& framework) {
    float x = 600.0f;
    float y = 50.0f;

    sf::Text header("Sensor Metrics", font, 18);
    header.setPosition(x, y);
    header.setFillColor(sf::Color::Cyan);
    window.draw(header);
    y += 30;

    for (const auto& pair : framework.getMetrics()) {
        std::stringstream ss;
        ss << pair.first << ":\n"
           << "  Min: " << pair.second.minVal << "\n"
           << "  Max: " << pair.second.maxVal << "\n"
           << "  Avg: " << pair.second.avgVal;
        
        sf::Text text(ss.str(), font, 14);
        text.setPosition(x, y);
        text.setFillColor(sf::Color::White);
        window.draw(text);
        y += 80;
    }
}
#endif
