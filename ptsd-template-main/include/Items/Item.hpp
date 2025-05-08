#ifndef ITEM_HPP
#define ITEM_HPP

#include "pch.hpp"

namespace Util {
    class Renderer;
}
class Character;

class Item {
    enum class ItemType {
        Potion,
        Weapon
    };
public:
    Item(std::string ImagePath, ItemType type, Util::Renderer *m_Root);
    virtual ~Item() = default;
    virtual void Use() = 0; // 使用道具的純虛擬函數
    virtual std::string GetType() const = 0; // 獲取道具類型的純虛擬函數
private:
    std::shared_ptr<Character> m_Icon; // 圖示
    ItemType m_Type; // 道具類型
};

#endif //ITEM_HPP