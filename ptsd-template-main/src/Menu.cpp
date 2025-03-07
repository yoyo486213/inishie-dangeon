#include "Menu.hpp"
#include "Util/Image.hpp"
#include "Util/Input.hpp"
#include "Util/Keycode.hpp"

Menu::Menu(const std::vector<std::string>& ImagePath) : Character(ImagePath[0]) { this->ImagePath = ImagePath; }

void Menu::MoveMenu(glm::vec2 displacement, glm::vec2 goal) {
    if (((goal[0] - this->GetPosition().x) * displacement[0] + (goal[1] - this->GetPosition().y) * displacement[1]) > 0) {
        this->SetPosition({this->GetPosition().x + displacement[0], this->GetPosition().y + displacement[1]});
    }
    else {
        this->state = false;
    }
}

bool Menu::IfFocus() {
    if((Util::Input::GetCursorPosition()[0] > (this->GetPosition()[0]-(this->GetScaledSize()[0]/2))) && (Util::Input::GetCursorPosition()[0] < (this->GetPosition()[0]+(this->GetScaledSize()[0]/2)))) {
        if ((Util::Input::GetCursorPosition()[1] > (this->GetPosition()[1]-(this->GetScaledSize()[1]/2))) && (Util::Input::GetCursorPosition()[1] < (this->GetPosition()[1]+(this->GetScaledSize()[1]/2)))) {
            return true;
        }
    }
    return false;
}

bool Menu::IfClick() {
    return Util::Input::IsKeyUp(Util::Keycode::MOUSE_LB);
}

void Menu::ChangeImage(int index) {
    this->SetImage(this->ImagePath[index - 1]);
}