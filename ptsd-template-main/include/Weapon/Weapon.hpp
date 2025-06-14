#ifndef WEAPON_HPP
#define WEAPON_HPP

#include "pch.hpp"
#include "IClickable.hpp"
#include "Weapon/Projectile.hpp"
#include "Items/Item.hpp"
#include "MyBGM.hpp"
#include <iostream>
#include <time.h>
#include <chrono>

class Player;
class Map;

class Weapon : public IClickable, public Item {
public:
    Weapon(std::string ImagePath, glm::vec2 attack,
           float attackCD, float skillMultiplier, int flightdistance,
           int skillCost, float skillCD)
        : Item(ImagePath), m_Attack(attack),
          m_SkillMultiplier(skillMultiplier),
          m_FlightDistance(flightdistance), m_SkillCost(skillCost),
          m_SkillCD(skillCD) { this->m_AttackCD = attackCD / 2;};
    
    virtual ~Weapon() = default;

    bool IfFocus() override;

    bool IfClick() override;

    bool IfPressed() override;

    void PlayWaveSFX() { m_WaveSFX->Play(0); }

    virtual void Skill(std::shared_ptr<Map> m_map, std::shared_ptr<Player> &m_Player, Util::Renderer *m_Root) = 0;

    int GetSkillCost() { return m_SkillCost; }

    float GetSkillCD() { return m_SkillCD; }
    void SetSkillCD(float skillCD) { m_SkillCD = skillCD; }
protected:
    glm::vec2 m_Attack;
    float m_AttackCD;

    float m_SkillMultiplier;
    int m_FlightDistance;
    int m_SkillCost;
    float m_SkillCD;
    std::shared_ptr<Map> m_map;
    std::shared_ptr<Player> m_Player;
    Util::Renderer *m_Root;
    std::shared_ptr<MyBGM> m_WaveSFX = std::make_shared<MyBGM>(RESOURCE_DIR"/BGM/sounds/WaveWeapon.wav");
};

#endif // WEAPON_HPP