#include "Projectile.h"

Projectile::Projectile(sf::Vector2f pos, sf::Vector2f dir, float speed, int dmg)
: velocity(dir * speed), damage(dmg), alive(true) {
    shape.setRadius(5.f);
    shape.setFillColor(sf::Color::Cyan);
    shape.setPosition(pos);
}

void Projectile::update(const sf::Time& dt) {
    shape.move(velocity * dt.asSeconds());
    sf::Vector2f pos = shape.getPosition();
    if (pos.x < -10 || pos.x > 810 || pos.y < -10 || pos.y > 610)
        alive = false;
}

void Projectile::draw(sf::RenderWindow& window) const {
    window.draw(shape);
}

sf::FloatRect Projectile::getBounds() const {
    return shape.getGlobalBounds();
}

bool Projectile::isAlive() const {
    return alive;
}

int Projectile::getDamage() const {
    return damage;
}

void Projectile::destroy() {
    alive = false;
}
