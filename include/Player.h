#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include "Item.h"

class Projectile;

class Player {
public:
    Player();

    void handleInput(const sf::Time& dt, std::vector<Projectile>& projectiles);
    void update(const sf::Time& dt);
    void draw(sf::RenderWindow& window) const;

    sf::Vector2f getPosition() const;
    sf::FloatRect getBounds() const;

    void takeDamage(int dmg);
    int getHealth() const;

    void increaseSpeed(float amount);
    void addHealth(int amount);
    void applyItem(const Item& item);
    const std::string& getCurrentItem() const;

    void setPosition(const sf::Vector2f& pos);

private:
    void shoot(std::vector<Projectile>& projectiles, const sf::Vector2f& dir);

    sf::RectangleShape shape;
    float speed;
    int health;
    std::string currentItem;
    float fireCooldown;
    sf::Clock fireTimer;
};

#endif
