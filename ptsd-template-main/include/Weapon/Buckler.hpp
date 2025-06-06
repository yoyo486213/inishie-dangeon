#ifndef BUCKLER_HPP
#define BUCKLER_HPP

#include "pch.hpp"
#include "Weapon/Weapon.hpp"
#include "IEquipable.hpp"

class Buckler : public IEquipable, public Weapon {
public:
    Buckler();

    void Equip(std::shared_ptr<Player> &m_Player) override;

    void UnEquip(std::shared_ptr<Player> &m_Player) override;

    void Skill(std::shared_ptr<Map> m_map, std::shared_ptr<Player> &m_Player, Util::Renderer *m_Root) override {
        (void)m_map;
        (void)m_Player;
        (void)m_Root;
    };
};

#endif // BUCKLER_HPP