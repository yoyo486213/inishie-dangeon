#include "Text.hpp"

Text::Text(const std::string& ImagePath) : Character(ImagePath) { this->ImagePath = ImagePath; }

Text::Text(const std::vector<std::string>& ImagePaths) : Character(ImagePaths[0]) { this->ImagePaths = ImagePaths; }

void Text::Move(glm::vec2 displacement, glm::vec2 goal) {
    if (((goal.x - this->GetPosition().x) * displacement.x + (goal.y - this->GetPosition().y) * displacement.y) > 0) {
        this->SetPosition(this->GetPosition() + displacement);
    }
    else {
        this->state = State::Stop;
    }
}

void Text::ChangeImage(int index) {
    this->SetImage(this->ImagePaths[index - 1]);
}