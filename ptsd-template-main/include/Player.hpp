#ifndef PLAYER_HPP
#define PLAYER_HPP


#include "pch.hpp"
#include "Character.hpp"

class Monster;
class ICollidable;

class Player : public Character {
public:
    Player(const std::string &ImagePath,
        int hp, int mp, glm::vec2 attack, int defense, int hitrate, int dodgerate, int criticalrate, int blockrate, std::vector<int> resistance, int gold, int exp);

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

    int GetGold() { return m_Gold; }

    int GetExp() { return m_Exp; }
private:
    int m_HP;
    int m_MP;
    glm::vec2 m_Attack;
    int m_Defense;
    int m_Hitrate;
    int m_Dodgerate;
    int m_Criticalrate;
    int m_Blockrate;
    std::vector<int> m_Resistance; // 火 冰 雷 毒 物

    int m_Gold;
    int m_Exp;
};

#endif //PLAYER_HPP