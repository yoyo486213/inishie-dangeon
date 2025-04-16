#include "Button.hpp"
#include "Util/Input.hpp"
#include "Util/Keycode.hpp"

Button::Button(const std::string& ImagePath) : Character(ImagePath) { this->ImagePath = ImagePath; }

Button::Button(const std::vector<std::string>& ImagePaths) : Character(ImagePaths[0]) { this->ImagePaths = ImagePaths; }

void Button::Move(glm::vec2 displacement, glm::vec2 goal) {
    if (((goal.x - this->GetPosition().x) * displacement.x + (goal.y - this->GetPosition().y) * displacement.y) > 0) {
        this->SetPosition(this->GetPosition() + displacement);
    }
    else {
        this->state = State::Stop;
    }
}

bool Button::IfFocus() {
    float Cursor_X = Util::Input::GetCursorPosition().x;
    float Cursor_Y = Util::Input::GetCursorPosition().y;
    float Menu_X_Range[2] = {(this->GetPosition().x - (this->GetScaledSize().x / 2)), (this->GetPosition().x + (this->GetScaledSize().x / 2))};
    float Menu_Y_Range[2] = {(this->GetPosition().y - (this->GetScaledSize().y / 2)), (this->GetPosition().y + (this->GetScaledSize().y / 2))};
    if((Cursor_X > Menu_X_Range[0]) && (Cursor_X < Menu_X_Range[1])) {
        if ((Cursor_Y > Menu_Y_Range[0]) && (Cursor_Y < Menu_Y_Range[1])) {
            return this->GetVisibility();
        }
    }
    return false;
}

bool Button::IfClick() {
    return Util::Input::IsKeyUp(Util::Keycode::MOUSE_LB) && IfFocus();
}

bool Button::IfPressed() {
    return Util::Input::IsKeyPressed(Util::Keycode::MOUSE_LB) && IfFocus();
}

void Button::ChangeImage(int index) {
    this->SetImage(this->ImagePaths[index - 1]);
}