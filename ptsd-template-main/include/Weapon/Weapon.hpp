#ifndef WEAPON_HPP
#define WEAPON_HPP

#include "pch.hpp"
#include "IClickable.hpp"
#include "Weapon/Projectile.hpp"
#include "Items/Item.hpp"

class Player;
class Map;

class Weapon : public IClickable, public Item {
public:
    Weapon(std::string ImagePath, glm::vec2 attack,
           float attackCD, float skillMultiplier, int skillRange,
           int skillCost, float skillCD)
        : Item(ImagePath), m_Attack(attack),
          m_AttackCD(attackCD), m_SkillMultiplier(skillMultiplier),
          m_SkillRange(skillRange), m_SkillCost(skillCost),
          m_SkillCD(skillCD) {};
    
    virtual ~Weapon() = default;

    bool IfFocus() override;

    bool IfClick() override;

    bool IfPressed() override;

    virtual void Skill(std::shared_ptr<Map> m_map, Util::Renderer *m_Root) = 0;

    virtual void Equip(std::shared_ptr<Player> &m_Player) = 0;
protected:
    glm::vec2 m_Attack;
    float m_AttackCD;
    float m_SkillMultiplier;
    int m_SkillRange;
    int m_SkillCost;
    float m_SkillCD;
};

#endif // WEAPON_HPP