#include "Monster/Monster.hpp"
#include <iostream>
#include "Calculation.hpp"

Monster::Monster(const std::vector<std::string> &ImagePaths,
    int hp, int mp, glm::vec2 attack, int defense, int hitrate, int dodgerate, std::vector<int> resistance, int gold, int exp, float TrackRange) 
    : Character(ImagePaths[0]), m_HP(hp), m_MP(mp), m_Attack(attack), m_Defense(defense), m_Hitrate(hitrate), m_Dodgerate(dodgerate), m_Resistance(resistance), m_Gold(gold), m_Exp(exp), m_TrackRange(TrackRange) {
        this->m_ImagePaths = ImagePaths;
}

void Monster::TakeDamage(int damage) {
    m_HP -= Calculation::CalcuDmg(damage, m_Defense, m_Resistance[4]);
    std::cout << "Monster HP: " << m_HP << std::endl;
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

    return xOverlap && yOverlap && this->GetVisibility();
}
