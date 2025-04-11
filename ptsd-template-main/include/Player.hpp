#ifndef PLAYER_HPP
#define PLAYER_HPP


#include "pch.hpp"
#include "Character.hpp"

class Monster;
class ICollidable;

class Player : public Character {
public:
    Player(const std::string &ImagePath);

    virtual ~Player() = default;

    int Attack();

    void Update(std::shared_ptr<Character> &m_map);

    void TakeDamage(int damage);

    int GetHP() const { return m_HP; }

    int GetMP() const { return m_MP; }

    glm::vec2 GetAttack() { return m_Attack; }

    int GetDefense() { return m_Defense; }

    int GetHitrate() { return m_Hitrate; }

    int GetDodgerate() { return m_Dodgerate;}

    int GetCriticalrate() { return m_Criticalrate; }

    int GetBlockrate() { return m_Blockrate; }

    std::vector<int> GetResistance() { return m_Resistance; }

    void SetAttackCD(float cd) { m_AttackCD = cd; }

    float GetAttackCD() const { return m_AttackCD; }

    int GetGold() { return m_Gold; }

    int GetExp() { return m_Exp; }
private:
    int m_HP = 1000;
    int m_MP = 20;
    glm::vec2 m_Attack = {1, 4};
    int m_Defense = 0;
    int m_Hitrate = 100;
    int m_Dodgerate = 0;
    int m_Criticalrate = 0;
    int m_Blockrate = 0;
    std::vector<int> m_Resistance = {0, 0, 0, 0, 0}; // 火 冰 雷 毒 物

    float m_AttackCD = 1.f;
    int m_Gold = 0;
    int m_Exp = 0;
};

#endif //PLAYER_HPP