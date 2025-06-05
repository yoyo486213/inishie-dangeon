#include "Weapon/Buckler.hpp"
#include "Player.hpp"
#include "Map/Map.hpp"
#include "App.hpp"

Buckler::Buckler()
    : Weapon(RESOURCE_DIR"/Weapon/Buckler.png", glm::vec2{0, 0}, 0, 0, 0, 0, 0.0f) {}

void Buckler::Equip(std::shared_ptr<Player> &m_Player) {
    m_Player->SetDefense(m_Player->GetDefense() + 5);
    m_Player->SetBlockrate(m_Player->GetBlockrate() + 10);
}

void Buckler::UnEquip(std::shared_ptr<Player> &m_Player) {
    m_Player->SetDefense(m_Player->GetDefense() - 5);
    m_Player->SetBlockrate(m_Player->GetBlockrate() - 10);
}