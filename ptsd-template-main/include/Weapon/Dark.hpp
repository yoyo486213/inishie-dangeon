#ifndef DARK_HPP
#define DARK_HPP

#include "pch.hpp"
#include "Weapon/Weapon.hpp"
#include "IEquipable.hpp"

class Dark : public IEquipable, public Weapon {
public:
    Dark();

    void Equip(std::shared_ptr<Player> &m_Player) override;

    void UnEquip(std::shared_ptr<Player> &m_Player) override;

    void Skill(std::shared_ptr<Map> m_map, std::shared_ptr<Player> &m_Player, Util::Renderer *m_Root) override;
};

#endif // DARK_HPP