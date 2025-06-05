#include "Monster/Monster.hpp"
#include <iostream>
#include "AnimatedCharacter.hpp"
#include "Calculation.hpp"
#include "Util/Input.hpp"

Monster::Monster(const std::vector<std::string> &ImagePaths,
    int hp, int mp, glm::vec2 attack, int defense, int hitrate, int dodgerate, std::vector<int> resistance, int gold, int exp, float TrackRange) 
    : Character(ImagePaths[0]), m_HP(hp), m_MP(mp), m_Attack(attack), m_Defense(defense), m_Hitrate(hitrate), m_Dodgerate(dodgerate), m_Resistance(resistance), m_Gold(gold), m_Exp(exp), m_TrackRange(TrackRange) {
        this->m_ImagePaths = ImagePaths;
        m_HPBox = std::make_shared<Character>(RESOURCE_DIR"/Monster/HPBox.png");
        m_HPBox->SetVisible(false);
        m_HPBox->SetZIndex(39);

        std::vector<std::string> HPProgressImages;
        HPProgressImages.reserve(50);
        for (int i = 1; i < 51; i++) {
            char buffer[200];
            snprintf(buffer, sizeof(buffer), RESOURCE_DIR"/Monster/HPProgress/HPBar-%02d.png", i);
            HPProgressImages.emplace_back(buffer);
        }
        m_HPBar = std::make_shared<AnimatedCharacter>(HPProgressImages);
        m_HPBar->SetVisible(false);
        m_HPBar->SetLooping(false);
        m_HPBar->SetZIndex(40);
}

void Monster::UpdateHPProgress() {
    if (this->IfFocus()) {
        m_HPBox->SetVisible(true);
        m_HPBar->SetVisible(true);
        m_HPBox->SetPosition(this->GetPosition() + glm::vec2{0, 20});
        m_HPBar->SetPosition(this->GetPosition() + glm::vec2{0, 20});
    }
    else {
        m_HPBox->SetVisible(false);
        m_HPBar->SetVisible(false);
    }

    int HPRate=float(this->GetHP())/float(this->GetMaxHP())*50;
    if (HPRate >= 1)
        m_HPBar->SetCurrentFrame(HPRate-1);
    else
        m_HPBar->SetCurrentFrame(HPRate);
}

void Monster::TakeDamage(int damage) {
    m_HP -= Calculation::CalcuDmg(damage, m_Defense, m_Resistance[4]);
    if (m_HP <= 0) {
        this->SetVisible(false);
    }
}

bool Monster::IsCollision(const std::shared_ptr<Character> &other, glm::vec2 displacement) {
    glm::vec2 thisSize = this->GetScaledSize();
    glm::vec2 otherSize = other->GetScaledSize();

    glm::vec2 thisPos = this->GetPosition() + displacement - glm::vec2({thisSize.x / 2.0, thisSize.y / 2.0});
    glm::vec2 otherPos = other->GetPosition() - glm::vec2({otherSize.x / 2.0, otherSize.y / 2.0});

    bool xOverlap = thisPos.x + thisSize.x > otherPos.x && otherPos.x + otherSize.x > thisPos.x;
    bool yOverlap = thisPos.y + thisSize.y > otherPos.y && otherPos.y + otherSize.y > thisPos.y;

    return xOverlap && yOverlap && this->GetVisibility() && other->GetVisibility();
}

bool Monster::IfFocus() {
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