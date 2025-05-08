#ifndef ITEM_HPP
#define ITEM_HPP

#include "pch.hpp"
#include "Character.hpp"

namespace Util {
    class Renderer;
}

class Item : public Character {
public:
    enum class ItemType {
        Ball,
        Potion,
        Weapon
    };

    Item(std::string ImagePath, ItemType type);

    virtual ~Item() = default;

    virtual void Use() = 0;

    ItemType GetType() { return m_Type; }
private:
    ItemType m_Type; // 道具類型
};

#endif //ITEM_HPP