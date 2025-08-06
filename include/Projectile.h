#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <SFML/Graphics.hpp>

class Projectile {
public:
    Projectile(sf::Vector2f pos, sf::Vector2f dir, float speed = 400.f, int dmg = 1);
    void update(const sf::Time& dt);
    void draw(sf::RenderWindow& window) const;
    sf::FloatRect getBounds() const;
    bool isAlive() const;
    int getDamage() const;
    void destroy();
private:
    sf::CircleShape shape;
    sf::Vector2f velocity;
    int damage;
    bool alive;
};

#endif
