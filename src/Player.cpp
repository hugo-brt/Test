#include "Player.h"
#include "Projectile.h"
#include <SFML/Window/Keyboard.hpp>

Player::Player() {
    shape.setSize({40.f, 40.f});
    shape.setFillColor(sf::Color::Green);
    shape.setPosition(400.f, 300.f);
    speed = 200.f;
    health = 6;
    fireCooldown = 0.3f;
}

void Player::setPosition(const sf::Vector2f& pos) {
    shape.setPosition(pos);
}

void Player::handleInput(const sf::Time& dt, std::vector<Projectile>& projectiles) {
    float seconds = dt.asSeconds();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) shape.move(0, -speed * seconds);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) shape.move(0, speed * seconds);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) shape.move(-speed * seconds, 0);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) shape.move(speed * seconds, 0);

    if (fireTimer.getElapsedTime().asSeconds() >= fireCooldown) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            shoot(projectiles, {0.f, -1.f});
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            shoot(projectiles, {0.f, 1.f});
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            shoot(projectiles, {-1.f, 0.f});
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            shoot(projectiles, {1.f, 0.f});
        }
    }
}

void Player::shoot(std::vector<Projectile>& projectiles, const sf::Vector2f& dir) {
    sf::Vector2f pos = shape.getPosition() + sf::Vector2f(shape.getSize().x/2, shape.getSize().y/2);
    projectiles.emplace_back(pos, dir);
    fireTimer.restart();
}

void Player::update(const sf::Time&) {
    // Placeholder for future updates (animations, etc.)
}

void Player::draw(sf::RenderWindow& window) const {
    window.draw(shape);
}

sf::Vector2f Player::getPosition() const {
    return shape.getPosition();
}

sf::FloatRect Player::getBounds() const {
    return shape.getGlobalBounds();
}

void Player::takeDamage(int dmg) {
    health -= dmg;
    if (health < 0) health = 0;
}

int Player::getHealth() const {
    return health;
}

void Player::increaseSpeed(float amount) {
    speed += amount;
}

void Player::addHealth(int amount) {
    health += amount;
}

void Player::applyItem(const Item& item) {
    item.apply(*this);
    currentItem = item.name;
}

const std::string& Player::getCurrentItem() const {
    return currentItem;
}
