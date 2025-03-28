#ifndef INVISIBLEWALL_HPP
#define INVISIBLEWALL_HPP

#include "pch.hpp"
#include "ICollidable.hpp"

class Character;

class InvisibleWall : public ICollidable {
public:
    InvisibleWall(glm::vec2 size);

    virtual ~InvisibleWall() = default;

    void SetPosition(glm::vec2 position) { m_Position = position; }

    glm::vec2 GetPosition() { return m_Position; }

    glm::vec2 GetSize() { return m_Size; }

    bool IsCollision(const std::shared_ptr<Character> &other, glm::vec2 displacement) override;

    void OnCollision() override {};

    void OffCollision() override {};
private:
    glm::vec2 m_Position;
    glm::vec2 m_Size;
};

#endif //INVISIBLEWALL_HPP