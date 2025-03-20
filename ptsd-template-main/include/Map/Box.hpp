#ifndef BOX_HPP
#define BOX_HPP

#include "pch.hpp"
#include "Character.hpp"
#include "Collidable.hpp"

class Box : public Collidable, public Character {
public:
    Box(const std::string& ImagePath);

    virtual ~Box() = default;

    bool IsCollision(glm::vec2 position) override;

    void OnCollision() override {};

    void OffCollision() override {};
};

#endif //BOX_HPP