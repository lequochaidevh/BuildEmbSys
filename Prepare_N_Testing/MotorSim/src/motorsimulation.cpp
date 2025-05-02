#include "motorsimulation.h"
#include <iostream>
#include <thread>
#include <chrono>

// Motor class implementation
Motor::Motor() : isRunning(false), speed(0) {}

void Motor::start() {
    isRunning = true;
}

void Motor::stop() {
    isRunning = false;
}

void Motor::setSpeed(int newSpeed) {
    if (newSpeed >= 0 && newSpeed <= 100) {
        speed = newSpeed;
    }
}

bool Motor::getIsRunning() const {
    return isRunning;
}

int Motor::getSpeed() const {
    return speed;
}

// MotorControl class implementation
MotorControl::MotorControl() : rotationAngle(0.0f) {
    // Set up motor circle
    motorCircle.setRadius(50);
    motorCircle.setFillColor(sf::Color::Green);
    motorCircle.setPosition(350, 250);

    // Set up motor shaft
    motorShaft.setSize(sf::Vector2f(100, 5));
    motorShaft.setFillColor(sf::Color::Black);
    motorShaft.setOrigin(0, 2);  // Origin at left center
    motorShaft.setPosition(400, 300);  // Center of the circle

    // Load font and set up status text
    if (!font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans-Bold.ttf")) {
        std::cout << "Error loading font" << std::endl;
        exit(-1);
    }
    statusText.setFont(font);
    statusText.setCharacterSize(24);
    statusText.setFillColor(sf::Color::White);
    statusText.setPosition(10, 10);
    statusText.setString("Motor is stopped.\nSpeed: 0%");
}

void MotorControl::handleEvents(sf::RenderWindow& window) {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
    }

    // Handle user input every 100ms
    if (sfmlClock.getElapsedTime().asMilliseconds() >= 100) {
        sfmlClock.restart();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {  // 'S' to start
            motor.start();
            motorCircle.setFillColor(sf::Color::Green);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::T)) {  // 'T' to stop
            motor.stop();
            motorCircle.setFillColor(sf::Color::Red);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {  // Up arrow to increase speed
            motor.setSpeed(motor.getSpeed() + 2);
            if (motor.getSpeed() > 100) motor.setSpeed(100);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {  // Down arrow to decrease speed
            motor.setSpeed(motor.getSpeed() - 2);
            if (motor.getSpeed() < 0) motor.setSpeed(0);
        }
    }
}

void MotorControl::update() {
    // Update status text
    std::string statusMessage = motor.getIsRunning() ?
        "Motor is running.\nSpeed: " + std::to_string(motor.getSpeed()) + "%" :
        "Motor is stopped.\nSpeed: " + std::to_string(motor.getSpeed()) + "%";
    statusText.setString(statusMessage);

    // Update motor shaft rotation
    if (motor.getIsRunning()) {
        rotationAngle += (motor.getSpeed() * motor.getSpeed() * 0.023f);
        if (rotationAngle >= 360) {
            rotationAngle = 0;
        }
        motorShaft.setRotation(rotationAngle);
    }
}

void MotorControl::render(sf::RenderWindow& window) {
    window.clear();
    window.draw(motorCircle);
    window.draw(motorShaft);
    window.draw(statusText);
    window.display();
}
