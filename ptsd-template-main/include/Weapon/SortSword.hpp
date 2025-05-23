#ifndef SORTSWORD_HPP
#define SORTSWORD_HPP

#include "pch.hpp"
#include "Weapon/Weapon.hpp"
#include "IUsable.hpp"
#include "IEquipable.hpp"
#include "Items/Item.hpp"

class SortSword : public Weapon, public IUsable {
public:
    SortSword();

    void Use() override {};

    // void Equip() override;

    void Skill() override;
};

#endif // SORTSWORD_HPP