#ifndef ICollidable_HPP
#define ICollidable_HPP

#include "pch.hpp"

class Character;

class ICollidable {
public:
    virtual ~ICollidable() = default;

    virtual bool IsCollision(const std::shared_ptr<Character> &other, glm::vec2 displacement) = 0;

    virtual void OnCollision() = 0;

    virtual void OffCollision() = 0;
};

#endif //ICollidable_HPP