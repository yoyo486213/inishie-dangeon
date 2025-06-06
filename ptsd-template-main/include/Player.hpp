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
        else if (this->GetHP() < 0) {
            this->m_HP = 0; // 確保生命值不會低於0
        }
    }

    int GetMP() const { return m_MP; }
    int GetMaxMP() const {return m_MaxMP; }
    void Restore_MP(int mp) { 
        this->m_MP += mp; 
        if (this->GetMP() > this->GetMaxMP()) {
            this->m_MP = this->GetMaxMP();
        }
        else if (this->GetMP() < 0) {
            this->m_MP = 0; // 確保魔法值不會低於0
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

    float GetDefaultAttackCD() const { return m_DefaultAttackCD; }
    void SetDefaultAttackCD(float cd) { m_DefaultAttackCD = cd; }

    int GetGold() { return m_Gold; }
    void SetGold(int gold) { 
        m_Gold += gold; 
        if (m_Gold < 0) {
            m_Gold = 0;
        }
    }

    int GetExp() { return m_Exp; }
    void Restore_EXP(int exp) { 
        m_Exp += exp; 
        if (m_Exp >= m_MaxExp && m_level < 100) {
            m_level++;
            m_Exp = 0;
            m_MaxExp = totalExp[m_level + 1] - totalExp[m_level]; // 每次升級增加100經驗值上限

            m_MaxHP += 5; // 每次升級增加5最大生命值
            m_HP = m_MaxHP; // 升級後恢復到最大生命值
            m_MaxMP += 2; // 每次升級增加2最大魔法值
            m_MP = m_MaxMP; // 升級後恢復到最大魔法值
            m_Attack += glm::vec2(1, 1); // 每次升級增加攻擊力
            m_Defense += 1; // 每次升級增加防禦力
            m_Hitrate += 1; // 每次升級增加命中率
            m_Dodgerate += 1; // 每次升級增加閃避率
        }
    }
    int GetMaxExp() { return m_MaxExp; }

    int GetLevel() const { return m_level; }
    void RestoreLever() { m_level += 1; }
private:
    int m_HP = 10000;
    int m_MaxHP = m_HP;
    int m_MP = 20;
    int m_MaxMP = m_MP;
    glm::vec2 m_Attack = {10, 40};
    int m_Defense = 0;
    int m_Hitrate = 100;
    int m_Dodgerate = 0;
    int m_Criticalrate = 0;
    int m_Blockrate = 0;
    std::vector<int> m_Resistance = {0, 0, 0, 0, 0}; // 火 冰 雷 毒 物

    float m_AttackCD = 1.f;
    float m_DefaultAttackCD = 1.f;
    int m_Gold = 0;
    int m_Exp = 0;
    int m_MaxExp = 40; // 初始經驗值上限

    int m_level = 1; // 玩家等級
    std::vector<int> totalExp = {
        0, 0, 40, 135, 320, 625, 1080, 1715, 2560, 3645, 
        5000, 6655, 8640, 10985, 13720, 16875, 20480, 24565, 29160, 34295,
        40000, 46305, 53240, 60835, 69120, 78125, 87880, 98415, 109760, 121945,
        135000, 148955, 163840, 179685, 196520, 214375, 233280, 253265, 274360, 296595,
        320000, 344605, 370440, 397535, 425920, 455625, 486680, 519115, 552960, 588245,
        625000, 663255, 703040, 744385, 787320, 831875, 878080, 925965, 975560, 1026895,
        1080000, 1134905, 1191640, 1250235, 1310720, 1373125, 1437480, 1503815, 1572160, 1642545,
        1715000, 1789555, 1866240, 1945085, 2026120, 2109375, 2194880, 2282665, 2372760, 2465195,
        2560000, 2657205, 2756840, 2858935, 2963520, 3070625, 3180280, 3292515, 3407360, 3524845,
        3645000, 3767855, 3893440, 4021785, 4152920, 4286875, 4423680, 4563365, 4705960, 4851495
    };
};

#endif //PLAYER_HPP