#include "Room.h"
#include "Player.h"
#include "Projectile.h"
#include <algorithm>
#include <cstdlib>

Room::Room() : bossRoom(false), portalSpawned(false) {
    itemShape.setSize({20.f, 20.f});
    itemShape.setFillColor(sf::Color::White);
}

void Room::generate(int difficulty, bool boss) {
    bossRoom = boss;
    portalSpawned = false;
    enemies.clear();
    item.reset();

    int enemyCount = boss ? 1 : (std::rand() % 3 + 1 + difficulty / 2);
    for (int i = 0; i < enemyCount; ++i) {
        sf::Vector2f pos(std::rand() % 760 + 20, std::rand() % 560 + 20);
        enemies.emplace_back(pos, boss && i == 0);
    }

    if (!boss && std::rand() % 5 == 0) {
        item = Item{ "Manual of Swift Cloud", [](Player& p) { p.increaseSpeed(50.f); } };
        itemShape.setPosition(390.f, 290.f);
    }
}

void Room::update(const sf::Time& dt, Player& player, std::vector<Projectile>& projectiles) {
    for (auto& e : enemies) {
        e.update(dt, player.getPosition());
        if (e.isAlive() && e.getBounds().intersects(player.getBounds())) {
            player.takeDamage(e.getContactDamage());
        }
    }

    for (auto& proj : projectiles) {
        for (auto& enemy : enemies) {
            if (proj.isAlive() && enemy.isAlive() && proj.getBounds().intersects(enemy.getBounds())) {
                enemy.takeDamage(proj.getDamage());
                proj.destroy();
            }
        }
    }

    enemies.erase(std::remove_if(enemies.begin(), enemies.end(), [](const Enemy& e) { return !e.isAlive(); }), enemies.end());

    if (bossRoom && enemies.empty() && !portalSpawned) {
        portalSpawned = true;
        portal.setRadius(25.f);
        portal.setFillColor(sf::Color::Magenta);
        portal.setPosition(400.f - 25.f, 300.f - 25.f);
    }
}

bool Room::tryPickItem(Player& player) {
    if (item && itemShape.getGlobalBounds().intersects(player.getBounds())) {
        player.applyItem(*item);
        item.reset();
        return true;
    }
    return false;
}

void Room::draw(sf::RenderWindow& window) {
    for (auto& e : enemies) e.draw(window);
    if (item) window.draw(itemShape);
    if (portalSpawned) window.draw(portal);
}

bool Room::isCleared() const {
    return enemies.empty();
}

bool Room::hasPortal() const {
    return portalSpawned;
}

sf::FloatRect Room::getPortalBounds() const {
    return portal.getGlobalBounds();
}
