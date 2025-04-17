#ifndef TEXT_HPP
#define TEXT_HPP

#include "pch.hpp"

#include "Character.hpp"
#include "IMoveable.hpp"

class Text : public Character, public IMoveable {
public:
    enum class State{
        Open,
        Close,
        Stop
    };

    explicit Text(const std::string& ImagePath);

    explicit Text(const std::vector<std::string>& ImagePaths);

    void Move(glm::vec2 displacement, glm::vec2 goal) override;

    void ChangeImage(int index);

private:
    State state = State::Stop;
    std::string ImagePath;
    std::vector<std::string> ImagePaths;
    std::string text;
};

#endif
