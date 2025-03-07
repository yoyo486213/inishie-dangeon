#ifndef MENU_HPP
#define MENU_HPP

#include "pch.hpp"

#include "Character.hpp"

class Menu : public Character {
public:
    explicit Menu(const std::string& ImagePath);

    void MoveMenu(glm::vec2 spawn, glm::vec2 displacement, glm::vec2 goal);
};

#endif
