#include "Items/Item.hpp"
#include "Util/Renderer.hpp"
#include "Character.hpp"

Item::Item(std::string ImagePath, ItemType type, Util::Renderer *m_Root) : m_Type(type) {
    m_Icon = std::make_shared<Character>(ImagePath);
    m_Icon->SetVisible(true);
    m_Icon->SetZIndex(40);
    m_Root->AddChild(m_Icon);
}

std::string Item::GetType() const {
    switch (m_Type) {
        case ItemType::Potion:
            return "Potion";
        case ItemType::Weapon:
            return "Weapon";
        default:
            return "Unknown";
    }
}