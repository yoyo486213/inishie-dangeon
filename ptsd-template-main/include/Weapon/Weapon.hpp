#ifndef WEAPON_HPP
#define WEAPON_HPP

#include "pch.hpp"
<<<<<<< HEAD
#include "IEquipable.hpp"
=======
>>>>>>> acb205481fa689122c59dd34a70ad5228ec03ee3
#include "Items/Item.hpp"

class Player;

class Weapon : public Item {
public:
    Weapon(std::string ImagePath, glm::vec2 attack,
           float attackCD, float skillMultiplier, int skillRange,
           int skillCost, float skillCD)
        : Item(ImagePath), m_Attack(attack),
          m_AttackCD(attackCD), m_SkillMultiplier(skillMultiplier),
          m_SkillRange(skillRange), m_SkillCost(skillCost),
          m_SkillCD(skillCD) {};
    
    virtual ~Weapon() = default;

<<<<<<< HEAD
    virtual bool useOnSelect() const override { return true; }

=======
>>>>>>> acb205481fa689122c59dd34a70ad5228ec03ee3
    virtual void Skill() = 0;
private:
    glm::vec2 m_Attack;
    float m_AttackCD;
    float m_SkillMultiplier;
    int m_SkillRange;
    int m_SkillCost;
    float m_SkillCD;
};

#endif // WEAPON_HPP