#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "../include/motorsimulation.h"  // Updated include directive
#include <thread>
#include <chrono>

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Motor Simulation");
    // Create a configuration for the motor
    struct MotorConfig config = {
        50.0f,                               // motorCircleRadius
        sf::Color::Green,                    // motorCircleColor
        sf::Vector2f(350, 250),              // motorCirclePosition
        sf::Vector2f(100, 5),                // motorShaftSize
        sf::Color::Black,                    // motorShaftColor
        sf::Vector2f(400, 300),              // motorShaftPosition
        24,                                  // fontSize
        sf::Color::White,                    // textColor
        sf::Vector2f(10, 10)                 // textPosition
    };

    // Initialize the MotorControl with the configuration
    MotorControl motorControl(config);
    //MotorControl motorControl;

    while (window.isOpen()) {
        motorControl.handleEvents(window);
        motorControl.update();
        motorControl.render(window);

        // Small delay for responsiveness
        std::this_thread::sleep_for(std::chrono::milliseconds(30));
    }

    return 0;
}
