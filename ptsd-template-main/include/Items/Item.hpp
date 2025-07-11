#ifndef ITEM_HPP
#define ITEM_HPP

#include "pch.hpp"
#include "Character.hpp"

namespace Util {
    class Renderer;
}

class Item : public Character {
public:
    Item(std::string ImagePath);

    virtual ~Item() = default;
};

#endif //ITEM_HPP