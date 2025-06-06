#ifndef SORTSWORD_HPP
#define SORTSWORD_HPP

#include "pch.hpp"
#include "Weapon/Weapon.hpp"
#include "IEquipable.hpp"

class SortSword : public IEquipable, public Weapon {
public:
    SortSword();

    void Equip() override;

    void UnEquip() override;

    void Skill(std::shared_ptr<Map> m_map, std::shared_ptr<Player> &m_Player, Util::Renderer *m_Root) override;
};

#endif // SORTSWORD_HPP