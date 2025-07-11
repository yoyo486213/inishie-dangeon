#ifndef BOW_HPP
#define BOW_HPP

#include "pch.hpp"
#include "Weapon/Weapon.hpp"
#include "IEquipable.hpp"

class Bow : public IEquipable, public Weapon {
public:
    Bow();

    void Equip(std::shared_ptr<Player> &m_Player) override;

    void UnEquip(std::shared_ptr<Player> &m_Player) override;

    void Attack(std::shared_ptr<Map> m_map, std::shared_ptr<Player> &m_Player, Util::Renderer *m_Root);

    void Skill(std::shared_ptr<Map> m_map, std::shared_ptr<Player> &m_Player, Util::Renderer *m_Root) override;
};

#endif // BOW_HPP