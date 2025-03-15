#ifndef MOVEANIMATED_HPP
#define MOVEANIMATED_HPP

#include "pch.hpp"
#include "Util/Input.hpp"
#include "Util/Keycode.hpp"

#include "AnimatedCharacter.hpp"
#include "IClickable.hpp"
#include "IMoveable.hpp"

class MoveAnimated : public AnimatedCharacter, public IClickable, public IMoveable {
public:
    explicit MoveAnimated(const std::vector<std::string>& ImagePaths);
    
    virtual ~MoveAnimated() = default;

    void Move(glm::vec2 displacement, glm::vec2 goal) override;

    void SetState(bool state) { this->state = state; }

    bool GetState() { return this->state; }

    bool IfFocus() override;

    bool IfClick() override;

    bool IfPressed() override;

private:
    bool state = false;
};

#endif
