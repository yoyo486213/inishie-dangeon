#include "Items/Orb.hpp"
#include "Util/Input.hpp"
#include <random>
#include "Player.hpp"

#include <iostream>

Orb::Orb(std::shared_ptr<Player> m_Player) : Character(RESOURCE_DIR"/Orb/Hp.png"), m_Player(m_Player) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(0, 1);

    switch (dis(gen)) {
    case 0: // HP藥水
        type = Type::Hp;
        this->ImagePaths = {
            RESOURCE_DIR "/Orb/Hp.png",
            RESOURCE_DIR "/Orb/Hp-Focus.png"
        };
        break;
    case 1: // MP藥水
        type = Type::Mp;
        this->ImagePaths = {
            RESOURCE_DIR "/Orb/Mp.png",
            RESOURCE_DIR "/Orb/Mp-Focus.png"
        };
        break;
    }
    this->ChangeImage(1);
}

bool Orb::IsCollision(const std::shared_ptr<Character> &other, glm::vec2 displacement) {
    glm::vec2 thisSize = this->GetScaledSize();
    glm::vec2 otherSize = other->GetScaledSize();

    glm::vec2 thisPos = this->GetPosition() + displacement - glm::vec2({thisSize.x / 2.0, thisSize.y / 2.0});
    glm::vec2 otherPos = other->GetPosition() - glm::vec2({otherSize.x / 2.0, otherSize.y / 2.0});

    bool xOverlap = thisPos.x + thisSize.x > otherPos.x && otherPos.x + otherSize.x > thisPos.x;
    bool yOverlap = thisPos.y + thisSize.y > otherPos.y && otherPos.y + otherSize.y > thisPos.y;

    return xOverlap && yOverlap && this->GetVisibility();
}

void Orb::OnCollision(std::shared_ptr<Player> &m_Player) {
    switch (this->type) {
        case Type::Hp:
            m_Player->SetHP(m_Player->GetHP() + 50);
            break;
        case Type::Mp:
            m_Player->SetMP(m_Player->GetMP() + 50);
            break;
    }
}

bool Orb::IfFocus() {
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

bool Orb::IfClick() {
    return Util::Input::IsKeyUp(Util::Keycode::MOUSE_LB) && IfFocus();
}

bool Orb::IfPressed() {
    return Util::Input::IsKeyPressed(Util::Keycode::MOUSE_LB) && IfFocus();
}