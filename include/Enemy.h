#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>

class Enemy {
public:
    Enemy(sf::Vector2f pos, bool boss = false);
    void update(const sf::Time& dt, const sf::Vector2f& playerPos);
    void draw(sf::RenderWindow& window) const;
    sf::FloatRect getBounds() const;
    void takeDamage(int dmg);
    bool isAlive() const;
    int getContactDamage() const;
private:
    sf::RectangleShape shape;
    float speed;
    int health;
    int contactDamage;
    bool alive;
};

#endif
