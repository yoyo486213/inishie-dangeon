#ifndef DESTRUCTIBLEOBJECT_HPP
#define DESTRUCTIBLEOBJECT_HPP

#include "pch.hpp"
#include "Character.hpp"
#include "ICollidable.hpp"

class DestructibleObject : public ICollidable, public Character {
public:
    DestructibleObject(const std::string &ImagePath);

    virtual ~DestructibleObject() = default;

    bool IsCollision(const std::shared_ptr<Character> &other, glm::vec2 displacement);

    void OnCollision() override;

    void OffCollision() override;
};

#endif //DESTRUCTIBLEOBJECT_HPP