#ifndef COLLIDABLE_HPP
#define COLLIDABLE_HPP

#include "pch.hpp"

class Collidable {
public:
    virtual ~Collidable() = default;

    virtual bool IsCollision(glm::vec2 position) = 0;

    virtual void OnCollision() = 0;

    virtual void OffCollision() = 0;

    // virtual glm::vec2 GetPosition() const = 0;
};

#endif //COLLIDABLE_HPP