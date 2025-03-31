#include "Player.hpp"
#include "Monster/Monster.hpp"
#include "Calculation.hpp"
#include <iostream>

Player::Player(const std::string &ImagePath,
    int hp, int mp, glm::vec2 attack, int defense, int hitrate, int dodgerate, int criticalrate, int blockrate, std::vector<int> resistance, int gold, int exp) 
    : Character(ImagePath), m_HP(hp), m_MP(mp), m_Attack(attack), m_Defense(defense), m_Hitrate(hitrate), m_Dodgerate(dodgerate), m_Criticalrate(criticalrate), m_Blockrate(blockrate), m_Resistance(resistance), m_Gold(gold), m_Exp(exp) {
        SetPosition({0, 0});
        SetVisible(true);
        SetZIndex(15);
}

int Player::Attack() {
    return 0;
}

void Player::Update(std::shared_ptr<Character> &m_map) {
    (void)m_map;
}

void Player::TakeDamage(int damage) {
    m_HP -= Calculation::CalcuDmg(damage, m_Defense, m_Resistance[4]);
    std::cout << "Player HP: " << m_HP << std::endl;
    if (m_HP <= 0) {
        this->SetVisible(false);
    }
}