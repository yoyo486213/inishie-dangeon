#include "Monster/Monster.hpp"
#include <iostream>
#include "Calculation.hpp"

Monster::Monster(const std::string &ImagePath,
    int hp, int mp, glm::vec2 attack, int defense, int hitrate, int dodgerate, std::vector<int> resistance, int gold, int exp, float TrackRange) 
    : Character(ImagePath), m_HP(hp), m_MP(mp), m_Attack(attack), m_Defense(defense), m_Hitrate(hitrate), m_Dodgerate(dodgerate), m_Resistance(resistance), m_Gold(gold), m_Exp(exp), m_TrackRange(TrackRange) {}

void Monster::TakeDamage(int damage) {
    m_HP -= Calculation::CalcuDmg(damage, m_Defense, m_Resistance[4]);
    std::cout << "Monster HP: " << m_HP << std::endl;
    if (m_HP <= 0) {
        this->SetVisible(false);
    }
}