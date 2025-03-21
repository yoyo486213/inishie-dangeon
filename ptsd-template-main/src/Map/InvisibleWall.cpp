#include "Map/InvisibleWall.hpp"

InvisibleWall::InvisibleWall(glm::vec2 size) {
    m_Size = size;
}

bool InvisibleWall::IsCollision(std::shared_ptr<Character> &other, glm::vec2 displacement) {
    glm::vec2 thisPos = this->GetPosition() + displacement;
    glm::vec2 otherPos = other->GetPosition();
    
    glm::vec2 thisSize = this->GetSize();
    glm::vec2 otherSize = other->GetScaledSize();

    bool xOverlap = thisPos.x + thisSize.x > otherPos.x && otherPos.x + otherSize.x > thisPos.x;
    bool yOverlap = thisPos.y + thisSize.y > otherPos.y && otherPos.y + otherSize.y > thisPos.y;

    return xOverlap && yOverlap;
}