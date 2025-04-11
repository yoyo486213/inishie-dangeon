#ifndef MONSTER_HPP
#define MONSTER_HPP

#include "pch.hpp"
#include "Character.hpp"

class ICollidable;
class Player;
class InvisibleWall;

class Monster : public Character {
public:
    Monster(const std::string &ImagePath,
        int hp, int mp, glm::vec2 attack, int defense, int hitrate, int dodgerate, std::vector<int> resistance, int gold, int exp, float TrackRange);

    virtual ~Monster() = default;
     
    virtual void Update( std::shared_ptr<Player> &m_Player, std::vector<std::shared_ptr<Character>> AllObjects, std::vector<std::shared_ptr<ICollidable>> AllCollidableObjects, std::vector<std::shared_ptr<InvisibleWall>> m_Invisiblewalls) = 0;

    virtual void TakeDamage(int damage);

    int GetHP() const { return m_HP; }

    int GetMP() const { return m_MP; }

    void SetAttackCD(float cd) { m_AttackCD = cd; }

    float GetAttackCD() const { return m_AttackCD; }
private:
    int m_HP;
    int m_MP;
public:
    const glm::vec2 m_Attack;
    const int m_Defense;
    const int m_Hitrate;
    const int m_Dodgerate;
    const std::vector<int> m_Resistance; // 火 冰 雷 毒 物理

    const int m_Gold;
    const int m_Exp;

    const float m_TrackRange;
    float m_AttackCD = 1.f;
};

#endif //MONSTER_HPP