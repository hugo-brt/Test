
#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>

class Player {
public:
    Player();
    void handleInput(const sf::Time& deltaTime);
    void draw(sf::RenderWindow& window);
private:
    sf::RectangleShape shape;
    float speed;
};

#endif
