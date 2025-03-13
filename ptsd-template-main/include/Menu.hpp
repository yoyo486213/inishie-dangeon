#ifndef MOVECHARACTER_HPP
#define MOVECHARACTER_HPP

#include "pch.hpp"

#include "Character.hpp"
#include "IClickable.hpp"
#include "IMoveable.hpp"

class Menu : public Character {
public:
    enum class State{
        Open,
        Close,
        Stop
    };

    explicit Menu(const std::string& ImagePath);

    explicit Menu(const std::vector<std::string>& ImagePaths);

    void Move(glm::vec2 displacement, glm::vec2 goal);

    void SetState(State state) { this->state = state; }

    void SetUsed(bool used) { this->used = used; }

    State GetState() { return this->state; }

    bool GetUsed() { return this->used; }

    bool IfFocus();

    bool IfClick();

    void ChangeImage(int index);

    virtual ~Menu() = default;

private:
    State state = State::Stop;
    bool used = false;
    std::string ImagePath;
    std::vector<std::string> ImagePaths;
};

#endif
