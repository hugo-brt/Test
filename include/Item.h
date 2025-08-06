#ifndef ITEM_H
#define ITEM_H

#include <functional>
#include <string>

class Player;

struct Item {
    std::string name;
    std::function<void(Player&)> apply;
};

#endif
