#include "Map/Unexplored.hpp"

Unexplored::Unexplored(const std::string& ImagePath) : Character(ImagePath){}

bool Unexplored::IfExplored(glm::vec2 position) {
    float x = GetPosition().x - 14;
    float y = GetPosition().y + 14;
    if (x <= position.x && x + GetScaledSize().x >= position.x && y >= position.y + 15 && y - GetScaledSize().y <= position.y + 15) {
        return true;
    }
    if (x <= position.x && x + GetScaledSize().x >= position.x && y >= position.y - 15 && y - GetScaledSize().y <= position.y - 15) {
        return true;
    }
    if (x <= position.x + 15 && x + GetScaledSize().x >= position.x + 15 && y >= position.y && y - GetScaledSize().y <= position.y) {
        return true;
    }
    if (x <= position.x - 15 && x + GetScaledSize().x >= position.x - 15 && y >= position.y && y - GetScaledSize().y <= position.y) {
        return true;
    }
    return false;
}