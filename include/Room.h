#ifndef ROOM_H
#define ROOM_H

#include <vector>
#include <optional>
#include <SFML/Graphics.hpp>
#include "Enemy.h"
#include "Item.h"

class Player;
class Projectile;

class Room {
public:
    Room();
    void generate(int difficulty, bool boss = false);
    void update(const sf::Time& dt, Player& player, std::vector<Projectile>& projectiles);
    void draw(sf::RenderWindow& window);
    bool isCleared() const;
    bool hasPortal() const;
    sf::FloatRect getPortalBounds() const;
    bool tryPickItem(Player& player);
private:
    std::vector<Enemy> enemies;
    std::optional<Item> item;
    sf::RectangleShape itemShape;
    bool bossRoom;
    bool portalSpawned;
    sf::CircleShape portal;
};

#endif
