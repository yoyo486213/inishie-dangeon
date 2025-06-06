#include "Weapon/Club.hpp"
#include "Weapon/Projectile.hpp"
#include "Util/Input.hpp"
#include "Player.hpp"
#include "Map/Map.hpp"
#include "App.hpp"

Club::Club()
    : Weapon(RESOURCE_DIR"/Weapon/Club/Club.png", glm::vec2{1, 5}, 1, 0.0f, 0, 20, 2.0f) {}

void Club::Equip(std::shared_ptr<Player> &m_Player) {
    m_Player->SetAttack(m_Player->GetAttack() + m_Attack);
    m_Player->SetDefaultAttackCD(m_Player->GetDefaultAttackCD() + this->m_AttackCD);
}

void Club::UnEquip(std::shared_ptr<Player> &m_Player) {
    m_Player->SetAttack(m_Player->GetAttack() - m_Attack);
    m_Player->SetDefaultAttackCD(m_Player->GetDefaultAttackCD() - this->m_AttackCD);
}

void Club::Skill(std::shared_ptr<Map> m_map, std::shared_ptr<Player> &m_Player, Util::Renderer *m_Root) {
    m_Player->Restore_HP((int)(m_Player->GetAttack().x + m_Player->GetAttack().y) / 2 + 10);
    auto projectile = std::make_shared<Projectile>(RESOURCE_DIR"/Weapon/Club/Effects.png", Util::Input::GetCursorPosition(), 0, glm::vec2(0, 0), m_FlightDistance, 0, 0.4f, Util::Input::GetCursorPosition(), ProjectileBehaviorType::HealingCircle, false);
    m_map->AddAllObjects(projectile);
    m_map->AddProjectile(projectile);
    m_Root->AddChild(projectile);
}