#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "motorsimulation.h"  // Updated include directive
#include <thread>
#include <chrono>

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Motor Simulation");
    MotorControl motorControl;

    while (window.isOpen()) {
        motorControl.handleEvents(window);
        motorControl.update();
        motorControl.render(window);

        // Small delay for responsiveness
        std::this_thread::sleep_for(std::chrono::milliseconds(30));
    }

    return 0;
}
