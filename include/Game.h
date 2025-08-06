#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <map>
#include <vector>
#include "Player.h"
#include "Room.h"
#include "Projectile.h"
#include "ResourceManager.h"

class Game {
public:
    Game();
    void run();
private:
    void processEvents();
    void update(sf::Time dt);
    void render();
    void handleRoomTransition();
    void loadFloor();
    void reset();

    sf::RenderWindow window;
    ResourceManager<sf::Font> fonts;
    Player player;
    std::vector<Projectile> projectiles;
    std::map<std::pair<int,int>, Room> rooms;
    std::pair<int,int> currentRoom;
    std::pair<int,int> bossRoom;
    int floor;
    sf::Font uiFont;
    sf::Text uiText;
    bool nextFloor;
};

#endif
