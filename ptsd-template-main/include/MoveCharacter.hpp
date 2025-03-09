#ifndef MOVECHARACTER_HPP
#define MOVECHARACTER_HPP

#include "pch.hpp"

#include "Character.hpp"

class MoveCharacter : public Character {
public:
    explicit MoveCharacter(const std::string& ImagePath);

    explicit MoveCharacter(const std::vector<std::string>& ImagePaths);

    void Move(glm::vec2 displacement, glm::vec2 goal);

    void Play() { this->state = true; }

    void Stop() { this->state = false; }

    bool GetState() { return this->state; }

    bool IfFocus();

    bool IfFocus(glm::vec2 pos);

    bool IfClick();

    void ChangeImage(int index);

private:
    bool state = false;
    std::string ImagePath;
    std::vector<std::string> ImagePaths;
};

#endif
