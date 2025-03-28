#include "Monster/Monster.hpp"
#include "SDL_mixer.h"

Monster::Monster(const std::string &ImagePath,
    int hp, int mp, std::vector<int> attack, int defense, int hitrate, int dodgerate, std::vector<int> resistance, int gold, int exp, float attackrange) 
    : Character(ImagePath), m_HP(hp), m_MP(mp), m_Attack(attack), m_Defense(defense), m_Hitrate(hitrate), m_Dodgerate(dodgerate), m_Resistance(resistance), m_Gold(gold), m_Exp(exp), m_AttackRange(attackrange) {
        SetPosition({-112, 0});
        SetVisible(true);
        SetZIndex(19);
}

void Monster::TakeDamage(int damage) {
    m_HP -= damage;
    if (m_HP <= 0) {
        this->SetVisible(false);
    }
}