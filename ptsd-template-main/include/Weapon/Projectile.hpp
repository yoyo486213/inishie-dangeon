#ifndef PROJECTILE_HPP
#define PROJECTILE_HPP

#include "pch.hpp"
#include "Character.hpp"
#include "IMoveable.hpp"
#include "ICollidable.hpp"

class Projectile : public IMoveable, public ICollidable, public Character {
public:
    Projectile(std::string ImagePath, glm::vec2 position, glm::vec2 direction, float speed, int damage)
        : Character(ImagePath), position(position), direction(direction), speed(speed), damage(damage) {}

    void Update() {
        position += direction * speed;
    }

    int GetDamage() const { return damage; }
private:
    glm::vec2 position;
    glm::vec2 direction;
    float speed;
    int damage;
};

#endif // PROJECTILE_HPP