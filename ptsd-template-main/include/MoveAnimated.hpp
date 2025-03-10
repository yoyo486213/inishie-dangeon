#ifndef MOVEANIMATED_HPP
#define MOVEANIMATED_HPP

#include "pch.hpp"

#include "AnimatedCharacter.hpp"

class MoveAnimated : public AnimatedCharacter {
public:
    explicit MoveAnimated(const std::vector<std::string>& ImagePaths);

    void Move(glm::vec2 displacement, glm::vec2 goal);

    void SetState(bool state) { this->state = state; }

    bool GetState() { return this->state; }

    bool IfFocus();

    bool IfClick();

private:
    bool state = false;
};

#endif
