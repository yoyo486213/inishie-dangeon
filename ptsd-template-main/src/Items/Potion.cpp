#include "Items/Potion.hpp"
#include <random>
#include "Util/Input.hpp"
#include "Player.hpp"

#include <iostream>

Potion::Potion(std::shared_ptr<Player> &m_Player) : Item(RESOURCE_DIR"/Potion/HpPotion.png", ItemType::Potion), m_Player(m_Player) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(0, 1);

    switch (dis(gen)) {
    case 0: // HP藥水
        type = Type::Hp;
        break;
    case 1: // MP藥水
        type = Type::Mp;
        this->SetImage(RESOURCE_DIR "/Potion/MpPotion.png");
        break;
    }
}

void Potion::Use() {
    std::cout << "use" << std::endl;
    // switch (GetType()) {
    //     case Type::Hp:
    //         m_Player->SetHP(m_Player->GetHP() + 50);
    //         std::cout << m_Player->GetHP() << std::endl;
    //     case Type::Mp:
    //         m_Player->SetMP(m_Player->GetMP() + 50);
    //         std::cout << m_Player->GetMP() << std::endl;
    // }
}

bool Potion::IfFocus() {
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

bool Potion::IfClick() {
    return Util::Input::IsKeyUp(Util::Keycode::MOUSE_LB) && IfFocus();
}

bool Potion::IfPressed() {
    return Util::Input::IsKeyPressed(Util::Keycode::MOUSE_LB) && IfFocus();
}