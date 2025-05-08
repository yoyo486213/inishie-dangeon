#include "Map/Props.hpp"
#include <random>
#include "Util/Input.hpp"
#include "Player.hpp"

Props::Props() : Character(RESOURCE_DIR"/Map/Props/Hp.png") {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(0, 4); // 0~3 是道具，4~8 是武器

    int itemIndex = dis(gen);

    switch (itemIndex) {
    case 0: // HP球
        type = "HP Ball";
        m_ImagePaths = {
            RESOURCE_DIR "/Map/Props/Hp.png",
            RESOURCE_DIR "/Map/Props/Hp-Focus.png"
        };
        break;
    case 1: // MP球
        type = "MP Ball";
        m_ImagePaths = {
            RESOURCE_DIR "/Map/Props/Mp.png",
            RESOURCE_DIR "/Map/Props/Mp-Focus.png"
        };
        break;
    case 2: // HP藥水
        type = "HP Potion";
        m_ImagePaths = {
            RESOURCE_DIR "/Map/Props/HpPotion.png",
            RESOURCE_DIR "/Map/Props/HpPotion.png"
        };
        break;
    case 3: // MP藥水
        type = "MP Potion";
        m_ImagePaths = {
            RESOURCE_DIR "/Map/Props/MpPotion.png",
            RESOURCE_DIR "/Map/Props/MpPotion.png"
        };
        break;
    case 4:
        type = "Sort Sword";
        m_ImagePaths = {
            RESOURCE_DIR "/Map/Weapon/SortSword.png",
            RESOURCE_DIR "/Map/Weapon/SortSword.png"
        };
        break;
    case 5:
        m_ImagePaths = {
            RESOURCE_DIR "/Map/Weapon/SortSword.png",
            RESOURCE_DIR "/Map/Weapon/SortSword.png"
        };
        break;
    case 6:
        m_ImagePaths = {
            RESOURCE_DIR "/Map/Weapon/SortSword.png",
            RESOURCE_DIR "/Map/Weapon/SortSword.png"
        };
        break;
    case 7:
        m_ImagePaths = {
            RESOURCE_DIR "/Map/Weapon/SortSword.png",
            RESOURCE_DIR "/Map/Weapon/SortSword.png"
        };
        break;
    case 8:
        m_ImagePaths = {
            RESOURCE_DIR "/Map/Weapon/SortSword.png",
            RESOURCE_DIR "/Map/Weapon/SortSword.png"
        };
        break;
    }

    this->ChangeImage(1);
}

bool Props::IsCollision(const std::shared_ptr<Character> &other, glm::vec2 displacement) {
    glm::vec2 thisSize = this->GetScaledSize();
    glm::vec2 otherSize = other->GetScaledSize();

    glm::vec2 thisPos = this->GetPosition() + displacement - glm::vec2({thisSize.x / 2.0, thisSize.y / 2.0});
    glm::vec2 otherPos = other->GetPosition() - glm::vec2({otherSize.x / 2.0, otherSize.y / 2.0});

    bool xOverlap = thisPos.x + thisSize.x > otherPos.x && otherPos.x + otherSize.x > thisPos.x;
    bool yOverlap = thisPos.y + thisSize.y > otherPos.y && otherPos.y + otherSize.y > thisPos.y;

    return xOverlap && yOverlap && this->GetVisibility();
}

void Props::OnCollision(std::shared_ptr<Player> &m_Player) {
    this->SetVisible(false);
    m_Player->SetHP(m_Player->GetHP() + 50);
}

bool Props::IfFocus() {
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