#ifndef SORTSWORD_HPP
#define SORTSWORD_HPP

#include "pch.hpp"
#include "Weapon/Weapon.hpp"
#include "Weapon/Projectile.hpp"

class SortSword : public Weapon {
public:
    SortSword();

    void Use() override;

    void Skill() override;
};

#endif // SORTSWORD_HPP