#ifndef SORTSWORD_HPP
#define SORTSWORD_HPP

#include "pch.hpp"
#include "Weapon/Weapon.hpp"
<<<<<<< HEAD
#include "Weapon/Projectile.hpp"
=======
#include "IEquipable.hpp"
#include "Items/Item.hpp"
>>>>>>> acb205481fa689122c59dd34a70ad5228ec03ee3

class SortSword : public Weapon{
public:
    SortSword();

<<<<<<< HEAD
    void Use() override;
=======
    // void Use() override;

    // void Equip() override;
>>>>>>> acb205481fa689122c59dd34a70ad5228ec03ee3

    void Skill() override;
};

#endif // SORTSWORD_HPP