#ifndef PLAYER_HPP
#define PLAYER_HPP


#include "pch.hpp"
#include "Character.hpp"

namespace Util {
    class Renderer;
}
class Monster;
class ICollidable;
class Button;
class Item;

class Player : public Character {
public:
    Player(const std::string &ImagePath, Util::Renderer *m_Root);

    virtual ~Player() = default;

    int Attack();

    void Update(std::shared_ptr<Character> &m_map);

    void TakeDamage(int damage);

    int GetHP() const { return m_HP; }
    int GetMaxHP() const {return m_MaxHP; }
    void Restore_HP(int hp) { 
        this->m_HP += hp; 
        if (this->GetHP() > this->GetMaxHP()) {
            this->m_HP = this->GetMaxHP();
        }
    }

    int GetMP() const { return m_MP; }
    int GetMaxMP() const {return m_MaxMP; }
    void Restore_MP(int mp) { 
        this->m_MP += mp; 
        if (this->GetMP() > this->GetMaxMP()) {
            this->m_MP = this->GetMaxMP();
        }
    }

    glm::vec2 GetAttack() { return m_Attack; }
    void SetAttack(const glm::vec2 &attack) { m_Attack = attack; }

    int GetDefense() { return m_Defense; }
    void SetDefense(int defense) { m_Defense = defense; }

    int GetHitrate() { return m_Hitrate; }
    void SetHitrate(int hitrate) { m_Hitrate = hitrate; }

    int GetDodgerate() { return m_Dodgerate;}
    void SetDodgerate(int dodgerate) { m_Dodgerate = dodgerate; }

    int GetCriticalrate() { return m_Criticalrate; }
    void SetCriticalrate(int criticalrate) { m_Criticalrate = criticalrate; }

    int GetBlockrate() { return m_Blockrate; }
    void SetBlockrate(int blockrate) { m_Blockrate = blockrate; }

    std::vector<int> GetResistance() { return m_Resistance; }
    void SetResistance(const std::vector<int> &resistance) { m_Resistance = resistance; }

    float GetAttackCD() const { return m_AttackCD; }
    void SetAttackCD(float cd) { m_AttackCD = cd; }

    int GetGold() { return m_Gold; }
    void SetGold(int gold) { 
        m_Gold += gold; 
        if (m_Gold < 0) {
            m_Gold = 0;
        }
    }

    int GetExp() { return m_Exp; }
    void SetExp(int exp) { 
        m_Exp += exp; 
        if (m_Exp < 0) {
            m_Exp = 0;
        }
        while (m_Exp >= m_MaxExp) {
            m_Exp -= m_MaxExp;
            m_MaxExp += 100; // 每次升級增加100經驗值上限
            m_MaxHP += 100; // 每次升級增加100最大生命值
            m_HP = m_MaxHP; // 升級後恢復到最大生命值
        }
    }
    int GetMaxExp() { return m_MaxExp; }
private:
    int m_HP = 10000;
    int m_MaxHP = m_HP;
    int m_MP = 20;
    int m_MaxMP = m_MP;
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
    int m_MaxExp = 100;
};

#endif //PLAYER_HPP