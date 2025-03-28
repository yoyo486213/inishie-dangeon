#ifndef MONSTER_HPP
#define MONSTER_HPP

#include "pch.hpp"
#include "Character.hpp"

class ICollidable;
class Player;

class Monster : public Character {
public:
    Monster(const std::string &ImagePath,
        int hp, int mp, std::vector<int> attack, int defense, int hitrate, int dodgerate, std::vector<int> resistance, int gold, int exp, float attackrange);

    virtual ~Monster() = default;

    virtual void Attack() = 0;
     
    virtual void Update(std::vector<std::shared_ptr<ICollidable>> AllCollidableObjects, std::shared_ptr<Player> &m_Player) = 0;

    virtual void TakeDamage(int damage);

    int GetDefense() { return m_Defense; }

    int GetHitrate() { return m_Hitrate; }

    int GetDodgerate() { return m_Dodgerate;}

    std::vector<int> GetResistance() { return m_Resistance; }

    int GetGold() { return m_Gold; }

    int GetExp() { return m_Exp; }
private:
    int m_HP;
    int m_MP;
public:
    std::vector<int> m_Attack;
    int m_Defense;
    int m_Hitrate;
    int m_Dodgerate;
    std::vector<int> m_Resistance; // 火 冰 雷 毒 物理

    int m_Gold;
    int m_Exp;

    const float m_AttackRange;
};

#endif //MONSTER_HPP