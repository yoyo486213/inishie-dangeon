#include "Map/InvisibleWall.hpp"

InvisibleWall::InvisibleWall(glm::vec2 size) {
    m_Size = size;
}

bool InvisibleWall::IsCollision(glm::vec2 position) {
    float width = 0;
    float hight = 0;
    if (position.x <= width && position.x + m_Size.x >= -width && position.y >= -hight && position.y - m_Size.y <= hight) {
        return true;
    }
    return false;
}