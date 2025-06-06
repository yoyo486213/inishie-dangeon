#ifndef IEQUIPABLE_HPP
#define IEQUIPABLE_HPP

#include "pch.hpp"

class Player;

class IEquipable {
public:
    virtual void Equip() = 0;

    virtual void UnEquip() = 0;

    virtual ~IEquipable() = default;
};

#endif //IEQUIPABLE_HPP