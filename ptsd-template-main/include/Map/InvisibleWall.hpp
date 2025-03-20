#ifndef INVISIBLEWALL_HPP
#define INVISIBLEWALL_HPP

#include "pch.hpp"
#include "Util/GameObject.hpp"

class InvisibleWall {
public:
    InvisibleWall(glm::vec2 size);

    virtual ~InvisibleWall() = default;

    void SetPosition(glm::vec2 position) { m_Position = position; }

    glm::vec2 GetPosition() { return m_Position; }

    bool IsCollision(glm::vec2 position);
private:
    glm::vec2 m_Position;
    glm::vec2 m_Size;
};

#endif //INVISIBLEWALL_HPP