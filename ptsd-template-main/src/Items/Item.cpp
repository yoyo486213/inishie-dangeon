#include "Items/Item.hpp"
#include "Util/Renderer.hpp"
#include "Character.hpp"

Item::Item(std::string ImagePath, ItemType type) : Character(ImagePath), m_Type(type) {
    this->SetVisible(true);
    this->SetZIndex(40);
}