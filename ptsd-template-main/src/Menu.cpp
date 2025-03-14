#include "Menu.hpp"

Menu::Menu(const std::string& ImagePath) : Character(ImagePath) { this->ImagePath = ImagePath; }

Menu::Menu(const std::vector<std::string>& ImagePaths) : Character(ImagePaths[0]) { this->ImagePaths = ImagePaths; }

void Menu::Move(glm::vec2 displacement, glm::vec2 goal) {
    if (((goal[0] - this->GetPosition().x) * displacement[0] + (goal[1] - this->GetPosition().y) * displacement[1]) > 0) {
        this->SetPosition({this->GetPosition().x + displacement[0], this->GetPosition().y + displacement[1]});
    }
    else {
        this->state = State::Stop;
    }
}

bool Menu::IfFocus() {
    int Cursor_X = Util::Input::GetCursorPosition()[0];
    int Cursor_Y = Util::Input::GetCursorPosition()[1];
    int Menu_X_Range[2] = {(this->GetPosition()[0] - (this->GetScaledSize()[0] / 2)), (this->GetPosition()[0] + (this->GetScaledSize()[0] / 2))};
    int Menu_Y_Range[2] = {(this->GetPosition()[1] - (this->GetScaledSize()[1] / 2)), (this->GetPosition()[1] + (this->GetScaledSize()[1] / 2))};
    if((Cursor_X > Menu_X_Range[0]) && (Cursor_X < Menu_X_Range[1])) {
        if ((Cursor_Y > Menu_Y_Range[0]) && (Cursor_Y < Menu_Y_Range[1])) {
            return true && GetVisibility();
        }
    }
    return false;
}

bool Menu::IfClick() {
    return Util::Input::IsKeyUp(Util::Keycode::MOUSE_LB) && IfFocus();
}

bool Menu::IfPressed() {
    return Util::Input::IsKeyDown(Util::Keycode::MOUSE_LB) && IfFocus();
}

void Menu::ChangeImage(int index) {
    this->SetImage(this->ImagePaths[index - 1]);
}