#include "Weapon/Weapon.hpp"
#include "Util/Input.hpp"

bool Weapon::IfFocus() {
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

bool Weapon::IfClick() {
    return Util::Input::IsKeyUp(Util::Keycode::MOUSE_LB) && IfFocus();
}

bool Weapon::IfPressed() {
    return Util::Input::IsKeyPressed(Util::Keycode::MOUSE_LB) && IfFocus();
}