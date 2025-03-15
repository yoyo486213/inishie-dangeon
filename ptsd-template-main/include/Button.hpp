#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "pch.hpp"
#include "Util/Input.hpp"
#include "Util/Keycode.hpp"

#include "Character.hpp"
#include "IClickable.hpp"
#include "IMoveable.hpp"



class Button : public Character, public IClickable, public IMoveable {
public:
    enum class State{
        Open,
        Close,
        Stop
    };

    explicit Button(const std::string& ImagePath);

    explicit Button(const std::vector<std::string>& ImagePaths);

    void Move(glm::vec2 displacement, glm::vec2 goal) override;

    void SetState(State state) { this->state = state; }

    State GetState() { return this->state; }

    bool IfFocus() override;

    bool IfClick() override;

    bool IfPressed() override;

    void ChangeImage(int index);

    virtual ~Button() = default;

private:
    State state = State::Stop;
    std::string ImagePath;
    std::vector<std::string> ImagePaths;
};

#endif
