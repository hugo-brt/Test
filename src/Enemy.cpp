#include "Enemy.h"
#include <cmath>

Enemy::Enemy(sf::Vector2f pos, bool boss) : alive(true) {
    shape.setSize({30.f, 30.f});
    shape.setPosition(pos);
    speed = boss ? 80.f : 100.f;
    health = boss ? 10 : 3;
    contactDamage = boss ? 2 : 1;
    shape.setFillColor(boss ? sf::Color::Red : sf::Color::Yellow);
}

void Enemy::update(const sf::Time& dt, const sf::Vector2f& playerPos) {
    if (!alive) return;
    sf::Vector2f dir = playerPos - shape.getPosition();
    float len = std::sqrt(dir.x * dir.x + dir.y * dir.y);
    if (len != 0) dir /= len;
    shape.move(dir * speed * dt.asSeconds());
}

void Enemy::draw(sf::RenderWindow& window) const {
    if (alive)
        window.draw(shape);
}

sf::FloatRect Enemy::getBounds() const {
    return shape.getGlobalBounds();
}

void Enemy::takeDamage(int dmg) {
    health -= dmg;
    if (health <= 0) alive = false;
}

bool Enemy::isAlive() const {
    return alive;
}

int Enemy::getContactDamage() const {
    return contactDamage;
}
