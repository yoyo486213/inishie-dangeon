#ifndef INVISIBLEWALL_HPP
#define INVISIBLEWALL_HPP

#include "pch.hpp"
#include "Util/GameObject.hpp"

class InvisibleWall : public Util::GameObject {
public:
    InvisibleWall(glm::vec2 position, glm::vec2 size) {
        m_Position = position;
        m_Size = size;
    }
private:
    glm::vec2 m_Position;
    glm::vec2 m_Size;
};

#endif //INVISIBLEWALL_HPP