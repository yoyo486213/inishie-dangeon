#ifndef UNEXPLORED_HPP
#define UNEXPLORED_HPP

#include "Character.hpp"
#include <glm/fwd.hpp>

class Unexplored : public Character {
public:
    Unexplored(const std::string& ImagePath);

    virtual ~Unexplored() = default;

    bool IfExplored(glm::vec2 position);
};

#endif //UNEXPLORED_HPP