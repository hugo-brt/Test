
#include <SFML/Graphics.hpp>
#include "Player.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Xianxia Isaac Clone");
    Player player;

    sf::Clock clock;
    while (window.isOpen()) {
        sf::Time deltaTime = clock.restart();

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        player.handleInput(deltaTime);

        window.clear();
        player.draw(window);
        window.display();
    }

    return 0;
}
