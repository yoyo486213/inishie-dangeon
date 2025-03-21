#ifndef INVISIBLEWALL_HPP
#define INVISIBLEWALL_HPP

#include "pch.hpp"
#include "Util/GameObject.hpp"
#include "Character.hpp"
#include <glm/fwd.hpp>

class InvisibleWall {
public:
    InvisibleWall(glm::vec2 size);

    virtual ~InvisibleWall() = default;

    void SetPosition(glm::vec2 position) { m_Position = position; }

    glm::vec2 GetPosition() { return m_Position; }

    glm::vec2 GetSize() { return m_Size; }

    bool IsCollision(std::shared_ptr<Character> &other, glm::vec2 displacement);
private:
    glm::vec2 m_Position;
    glm::vec2 m_Size;
};

#endif //INVISIBLEWALL_HPP