#ifndef MOTORSIMULATION_H
#define MOTORSIMULATION_H

#include <SFML/Graphics.hpp>
struct MotorConfig {
    float motorCircleRadius;     // Radius of the motor circle
    sf::Color motorCircleColor;  // Color of the motor circle
    sf::Vector2f motorCirclePosition; // Position of the motor circle

    sf::Vector2f motorShaftSize; // Size of the motor shaft
    sf::Color motorShaftColor;   // Color of the motor shaft
    sf::Vector2f motorShaftPosition; // Position of the motor shaft

    int fontSize;               // Font size for the status text
    sf::Color textColor;        // Color of the status text
    sf::Vector2f textPosition;  // Position of the status text
};

class Motor {
private:
    bool isRunning;  // Motor status (running or stopped)
    int speed;       // Motor speed (from 0 to 100)

public:
    Motor();  // Constructor declaration

    void start();
    void stop();
    void setSpeed(int newSpeed);
    bool getIsRunning() const;
    int getSpeed() const;
};

class MotorControl {
private:
    Motor motor;  // Motor object
    sf::CircleShape motorCircle;  // Motor body representation
    sf::RectangleShape motorShaft;  // Motor shaft representation
    sf::Text statusText;  // Text to display motor status
    sf::Font font;  // Font for status text
    float rotationAngle;  // Rotation angle for the motor shaft
    sf::Clock sfmlClock;  // Clock to manage timing

public:
    MotorControl(const MotorConfig& config);  // Constructor to set up graphical elements

    void handleEvents(sf::RenderWindow& window);  // Handle window events and user input
    void update();  // Update motor state and visuals
    void render(sf::RenderWindow& window);  // Draw everything to the window
};

#endif // MOTORSIMULATION_H
