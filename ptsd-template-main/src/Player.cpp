#include "Player.hpp"
#include "Monster/Monster.hpp"
#include "Calculation.hpp"
#include <iostream>

Player::Player(const std::string &ImagePath) : Character(ImagePath) {
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