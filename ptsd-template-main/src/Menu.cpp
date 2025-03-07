#include "Menu.hpp"
#include "Util/Image.hpp"

Menu::Menu(const std::string& ImagePath) : Character(ImagePath) {}

void Menu::MoveMenu(glm::vec2 spawn, glm::vec2 displacement, glm::vec2 goal) {
    this->SetPosition(spawn);
    while (((goal[0] - this->GetPosition().x) * displacement[0] + (goal[1] - this->GetPosition().y) * displacement[1]) > 0) {
        this->SetPosition({this->GetPosition().x + displacement[0], this->GetPosition().y + displacement[1]});
    }
}