#include "Map/Box.hpp"

Box::Box(const std::string& ImagePath) : Character(ImagePath) {}

bool Box::IsCollision(std::shared_ptr<Character> &other, glm::vec2 displacement) {
    glm::vec2 thisPos = this->GetPosition() + displacement;
    glm::vec2 otherPos = other->GetPosition();
    
    glm::vec2 thisSize = this->GetScaledSize();
    glm::vec2 otherSize = other->GetScaledSize();

    bool xOverlap = thisPos.x + thisSize.x > otherPos.x && otherPos.x + otherSize.x > thisPos.x;
    bool yOverlap = thisPos.y + thisSize.y > otherPos.y && otherPos.y + otherSize.y > thisPos.y;

    return xOverlap && yOverlap;
}