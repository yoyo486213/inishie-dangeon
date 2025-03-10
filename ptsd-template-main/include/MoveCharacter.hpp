#ifndef MOVECHARACTER_HPP
#define MOVECHARACTER_HPP

#include "pch.hpp"

#include "Character.hpp"

class MoveCharacter : public Character {
public:
    explicit MoveCharacter(const std::string& ImagePath);

    explicit MoveCharacter(const std::vector<std::string>& ImagePaths);

    void Move(glm::vec2 displacement, glm::vec2 goal);

    void SetState(bool state) { this->state = state; }

    void SetUsed(bool used) { this->used = used; }

    bool GetState() { return this->state; }

    bool GetUsed() { return this->used; }

    bool IfFocus();

    bool IfClick();

    void ChangeImage(int index);

private:
    bool state = false;
    bool used = false;
    std::string ImagePath;
    std::vector<std::string> ImagePaths;
};

#endif
