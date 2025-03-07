#ifndef MENU_HPP
#define MENU_HPP

#include "pch.hpp"

#include "Character.hpp"

class Menu : public Character {
public:
    explicit Menu(const std::vector<std::string>& ImagePath);

    void MoveMenu(glm::vec2 displacement, glm::vec2 goal);

    void Play() { this->state = true; }

    void Stop() { this->state = false; }

    bool GetState() { return this->state; }

    bool IfFocus();

    bool IfClick();

    void ChangeImage(int index);

private:
    bool state = false;
    std::vector<std::string> ImagePath;
};

#endif
