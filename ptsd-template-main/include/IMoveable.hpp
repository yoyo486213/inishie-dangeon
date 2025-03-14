#ifndef IMOVEABLE_HPP
#define IMOVEABLE_HPP

#include "pch.hpp"

class IMoveable {
public:
    virtual void Move(glm::vec2 displacement, glm::vec2 goal) = 0;

    virtual ~IMoveable() = default;
};

#endif //IMOVEABLE_HPP