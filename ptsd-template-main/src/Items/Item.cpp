#include "Items/Item.hpp"
#include "Util/Renderer.hpp"
#include "Character.hpp"

Item::Item(std::string ImagePath) : Character(ImagePath) {
    this->SetVisible(true);
    this->SetZIndex(40);
}