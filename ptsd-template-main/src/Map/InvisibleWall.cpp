#include "Map/InvisibleWall.hpp"
#include <iostream>

InvisibleWall::InvisibleWall(glm::vec2 size) {
    m_Size = size;
}

bool InvisibleWall::IsCollision(glm::vec2 position) {
    if (position.x <= 0 && position.x + m_Size.x >= 0 && position.y >= 0 && position.y - m_Size.y <= 0) {
        return true;
    }
    return false;
}