#ifndef IEQUIPABLE_HPP
#define IEQUIPABLE_HPP

#include "pch.hpp"

class Player;

class IEquipable {
public:
    virtual void Equip(std::shared_ptr<Player> &m_Player) = 0;

    virtual void UnEquip(std::shared_ptr<Player> &m_Player) = 0;

    virtual ~IEquipable() = default;
};

#endif //IEQUIPABLE_HPP