#include "Game.h"
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <algorithm>

Game::Game() : window(sf::VideoMode(800, 600), "Xianxia Isaac Clone"), currentRoom({0,0}), floor(1), nextFloor(false) {
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    try {
        uiFont = *fonts.get("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf");
    } catch (...) {
        // Font loading failure is non-fatal
    }
    uiText.setFont(uiFont);
    uiText.setCharacterSize(16);
    uiText.setFillColor(sf::Color::White);

    loadFloor();
}

void Game::loadFloor() {
    rooms.clear();
    projectiles.clear();
    currentRoom = {0,0};
    do {
        bossRoom = {std::rand()%3 - 1, std::rand()%3 - 1};
    } while (bossRoom == currentRoom);

    Room start;
    start.generate(floor, false);
    rooms[currentRoom] = start;
    player.setPosition({400.f, 300.f});
    nextFloor = false;
}

void Game::run() {
    sf::Clock clock;
    while (window.isOpen()) {
        processEvents();
        sf::Time dt = clock.restart();
        update(dt);
        render();
    }
}

void Game::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
    }
}

void Game::update(sf::Time dt) {
    player.handleInput(dt, projectiles);

    for (auto& p : projectiles) p.update(dt);
    projectiles.erase(std::remove_if(projectiles.begin(), projectiles.end(), [](const Projectile& p){ return !p.isAlive(); }), projectiles.end());

    Room& room = rooms[currentRoom];
    room.update(dt, player, projectiles);
    room.tryPickItem(player);

    if (room.hasPortal() && player.getBounds().intersects(room.getPortalBounds())) {
        nextFloor = true;
    }

    handleRoomTransition();

    if (nextFloor) {
        ++floor;
        loadFloor();
    }

    if (player.getHealth() <= 0) {
        reset();
    }

    std::ostringstream ss;
    ss << "Qi: " << player.getHealth() << "\nFloor: " << floor << "\nItem: " << player.getCurrentItem();
    uiText.setString(ss.str());
}

void Game::handleRoomTransition() {
    sf::Vector2f pos = player.getPosition();
    bool moved = false;
    if (pos.x < 0) {
        currentRoom.first--;
        player.setPosition({780.f, pos.y});
        moved = true;
    } else if (pos.x > 800 - 40) {
        currentRoom.first++;
        player.setPosition({0.f, pos.y});
        moved = true;
    } else if (pos.y < 0) {
        currentRoom.second--;
        player.setPosition({pos.x, 580.f});
        moved = true;
    } else if (pos.y > 600 - 40) {
        currentRoom.second++;
        player.setPosition({pos.x, 0.f});
        moved = true;
    }

    if (moved) {
        auto it = rooms.find(currentRoom);
        if (it == rooms.end()) {
            Room newRoom;
            bool boss = (currentRoom == bossRoom);
            newRoom.generate(floor, boss);
            rooms[currentRoom] = newRoom;
        }
    }
}

void Game::render() {
    window.clear();
    rooms[currentRoom].draw(window);
    for (auto& p : projectiles) p.draw(window);
    player.draw(window);
    window.draw(uiText);
    window.display();
}

void Game::reset() {
    floor = 1;
    player = Player();
    loadFloor();
}
