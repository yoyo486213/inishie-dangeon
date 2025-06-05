#include "Weapon/FireRod.hpp"
#include "Weapon/Projectile.hpp"
#include "Util/Input.hpp"
#include "Player.hpp"
#include "Map/Map.hpp"
#include "App.hpp"

FireRod::FireRod()
    : Weapon(RESOURCE_DIR"/Weapon/FireRod/FireRod.png", glm::vec2{2, 6}, 2, 1.0f, 9999, 12, 2.0f) {}

void FireRod::Equip(std::shared_ptr<Player> &m_Player) {
    m_Player->SetAttack(m_Player->GetAttack() + m_Attack);
    m_Player->SetDefaultAttackCD(m_Player->GetDefaultAttackCD() + this->m_AttackCD);
}

void FireRod::UnEquip(std::shared_ptr<Player> &m_Player) {
    m_Player->SetAttack(m_Player->GetAttack() - m_Attack);
    m_Player->SetDefaultAttackCD(m_Player->GetDefaultAttackCD() - this->m_AttackCD);
}

void FireRod::Skill(std::shared_ptr<Map> m_map, std::shared_ptr<Player> &m_Player, Util::Renderer *m_Root) {
    auto projectile = std::make_shared<Projectile>(RESOURCE_DIR"/Weapon/FireRod/Projectile.png", Util::Input::GetCursorPosition(), 4, glm::vec2(((m_Player->GetAttack().x + m_Player->GetAttack().y) / 2 + (int)(m_Player->GetLevel() * 0.75f)) * 2 + 5), m_FlightDistance);
    m_map->AddAllObjects(projectile);
    m_map->AddProjectile(projectile);
    m_Root->AddChild(projectile);
}