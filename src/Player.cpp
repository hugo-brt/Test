
#include "Player.h"

Player::Player() {
    shape.setSize(sf::Vector2f(40.0f, 40.0f));
    shape.setFillColor(sf::Color::Green);
    shape.setPosition(400.0f, 300.0f);
    speed = 200.0f; // pixels per second
}

void Player::handleInput(const sf::Time& deltaTime) {
    float dt = deltaTime.asSeconds();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) shape.move(0, -speed * dt);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) shape.move(0, speed * dt);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) shape.move(-speed * dt, 0);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) shape.move(speed * dt, 0);
}

void Player::draw(sf::RenderWindow& window) {
    window.draw(shape);
}
