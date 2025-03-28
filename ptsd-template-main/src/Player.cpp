#include "Player.hpp"
#include "Monster/Monster.hpp"

Player::Player(const std::string &ImagePath,
    int hp, int mp, std::vector<int> attack, int defense, int hitrate, int dodgerate, std::vector<int> resistance, int gold, int exp) 
    : Character(ImagePath), m_HP(hp), m_MP(mp), m_Attack(attack), m_Defense(defense), m_Hitrate(hitrate), m_Dodgerate(dodgerate), m_Resistance(resistance), m_Gold(gold), m_Exp(exp) {
        SetPosition({0, 0});
        SetVisible(true);
        SetZIndex(15);
}

void Player::Attack() {

}

void Player::Update(std::shared_ptr<Character> &m_map) {
    (void)m_map;
    // for (const auto& monster : m_map)
    // if (this->IsCollision())
}

void Player::TakeDamage(int damage) {
    m_HP -= damage;
    if (m_HP <= 0) {
        this->SetVisible(false);
    }
}