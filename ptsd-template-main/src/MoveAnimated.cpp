#include "MoveAnimated.hpp"
#include "Util/Input.hpp"
#include "Util/Keycode.hpp"

MoveAnimated::MoveAnimated(const std::vector<std::string>& ImagePaths) : AnimatedCharacter(ImagePaths) {}

void MoveAnimated::Move(glm::vec2 displacement, glm::vec2 goal) {
    if (((goal[0] - this->GetPosition().x) * displacement[0] + (goal[1] - this->GetPosition().y) * displacement[1]) > 0) {
        this->SetPosition(this->GetPosition() + displacement);
    }
    else {
        this->state = false;
    }
}

bool MoveAnimated::IfFocus() {
    float Cursor_X = Util::Input::GetCursorPosition()[0];
    float Cursor_Y = Util::Input::GetCursorPosition()[1];
    float Menu_X_Range[2] = {(this->GetPosition().x - (this->GetScaledSize().x / 2)), (this->GetPosition().x + (this->GetScaledSize().x / 2))};
    float Menu_Y_Range[2] = {(this->GetPosition().y - (this->GetScaledSize().y / 2)), (this->GetPosition().y + (this->GetScaledSize().y / 2))};
    if((Cursor_X > Menu_X_Range[0]) && (Cursor_X < Menu_X_Range[1])) {
        if ((Cursor_Y > Menu_Y_Range[0]) && (Cursor_Y < Menu_Y_Range[1])) {
            return this->GetVisibility();
        }
    }
    return false;
}

bool MoveAnimated::IfClick() {
    return Util::Input::IsKeyUp(Util::Keycode::MOUSE_LB) && IfFocus();
}

bool MoveAnimated::IfPressed() {
    return Util::Input::IsKeyDown(Util::Keycode::MOUSE_LB) && IfFocus();
}