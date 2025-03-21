#ifndef BOX_HPP
#define BOX_HPP

#include "pch.hpp"
#include "Character.hpp"

class Box : public Character {
public:
    Box(const std::string& ImagePath);

    virtual ~Box() = default;

    bool IsCollision(std::shared_ptr<Character> &other, glm::vec2 displacement);
};

#endif //BOX_HPP