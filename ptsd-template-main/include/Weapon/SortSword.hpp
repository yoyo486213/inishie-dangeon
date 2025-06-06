#ifndef SORTSWORD_HPP
#define SORTSWORD_HPP

#include "pch.hpp"
#include "Weapon/Weapon.hpp"

class SortSword : public Weapon {
public:
    SortSword(std::shared_ptr<Map> m_map, std::shared_ptr<Player> m_Player, Util::Renderer *m_Root);

    void Equip() override;

    void UnEquip() override;

    void Skill(std::shared_ptr<Map> m_map, Util::Renderer *m_Root) override;
};

#endif // SORTSWORD_HPP