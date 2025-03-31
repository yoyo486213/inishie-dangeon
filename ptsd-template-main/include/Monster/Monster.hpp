#ifndef MONSTER_HPP
#define MONSTER_HPP

#include "pch.hpp"
#include "Character.hpp"

class ICollidable;
class Player;

class Monster : public Character {
public:
    Monster(const std::string &ImagePath,
        int hp, int mp, glm::vec2 attack, int defense, int hitrate, int dodgerate, std::vector<int> resistance, int gold, int exp, float TrackRange);

    virtual ~Monster() = default;

    virtual int Attack() = 0;
    // int AttackerDmg(int baseDmg, int CriticalRate, ) {

    // };
     
    virtual void Update(std::vector<std::shared_ptr<Character>> AllObjects, std::vector<std::shared_ptr<ICollidable>> AllCollidableObjects, std::shared_ptr<Player> &m_Player) = 0;

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
    const glm::vec2 m_Attack;
    const int m_Defense;
    const int m_Hitrate;
    const int m_Dodgerate;
    const std::vector<int> m_Resistance; // 火 冰 雷 毒 物理

    const int m_Gold;
    const int m_Exp;

    const float m_TrackRange;
};

#endif //MONSTER_HPP