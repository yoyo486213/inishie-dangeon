#ifndef WEAPON_HPP
#define WEAPON_HPP

#include "pch.hpp"
#include "IClickable.hpp"
#include "IEquipable.hpp"
#include "IUsable.hpp"
#include "Weapon/Projectile.hpp"
#include "Items/Item.hpp"
#include <iostream>
#include <time.h>
#include <chrono>

class Player;
class Map;

class Weapon : public IClickable, public IEquipable, public IUsable, public Item {
public:
    Weapon(std::string ImagePath, glm::vec2 attack,
           float attackCD, float skillMultiplier, int skillRange,
           int skillCost, float skillCD,
           std::shared_ptr<Map> &map,
           std::shared_ptr<Player> &Player,
           Util::Renderer *Root)
        : Item(ImagePath), m_Attack(attack),
          m_AttackCD(attackCD), m_SkillMultiplier(skillMultiplier),
          m_SkillRange(skillRange), m_SkillCost(skillCost),
          m_SkillCD(skillCD),m_map(map),
          m_Player(Player),m_Root(Root) {};
    
    virtual ~Weapon() = default;

    bool IfFocus() override;

    bool IfClick() override;

    bool IfPressed() override;

    int GetCooldownPercent();

    bool Use() override;

    virtual void Skill(std::shared_ptr<Map> m_map, Util::Renderer *m_Root) = 0;
protected:
    glm::vec2 m_Attack;
    float m_AttackCD;
    float m_SkillMultiplier;
    int m_SkillRange;
    int m_SkillCost;
    float m_SkillCD;
    std::chrono::time_point<std::chrono::high_resolution_clock> Use_time;
    std::shared_ptr<Map> m_map;
    std::shared_ptr<Player> m_Player;
    Util::Renderer *m_Root;
};

#endif // WEAPON_HPP