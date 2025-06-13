#include "Weapon/IceRod.hpp"
#include "Weapon/Projectile.hpp"
#include "Util/Input.hpp"
#include "Player.hpp"
#include "Map/Map.hpp"
#include "App.hpp"

IceRod::IceRod()
    : Weapon(RESOURCE_DIR"/Weapon/IceRod/IceRod.png", glm::vec2{3, 5}, 4, 1.0f, 9999, 12, 2.0f) {}

void IceRod::Equip(std::shared_ptr<Player> &m_Player) {
    m_Player->SetAttack(m_Player->GetAttack() + m_Attack);
    m_Player->SetDefaultAttackCD(m_Player->GetDefaultAttackCD() + this->m_AttackCD);
}

void IceRod::UnEquip(std::shared_ptr<Player> &m_Player) {
    m_Player->SetAttack(m_Player->GetAttack() - m_Attack);
    m_Player->SetDefaultAttackCD(m_Player->GetDefaultAttackCD() - this->m_AttackCD);
}

void IceRod::Skill(std::shared_ptr<Map> m_map, std::shared_ptr<Player> &m_Player, Util::Renderer *m_Root) {
    PlayWaveSFX();
    auto projectile = std::make_shared<Projectile>(RESOURCE_DIR"/Weapon/IceRod/Projectile.png", Util::Input::GetCursorPosition(), 4, glm::vec2(((m_Player->GetAttack().x + m_Player->GetAttack().y) / 2 + (int)(m_Player->GetLevel() * 0.75f)) * 2 + 5), m_FlightDistance);
    m_map->AddAllObjects(projectile);
    m_map->AddProjectile(projectile);
    m_Root->AddChild(projectile);
}