#include "Weapon/HunterBow.hpp"
#include "Weapon/Projectile.hpp"
#include "Util/Input.hpp"
#include "Player.hpp"
#include "Map/Map.hpp"
#include "App.hpp"

HunterBow::HunterBow()
    : Weapon(RESOURCE_DIR"/Weapon/HunterBow/HunterBow.png", glm::vec2{4, 8}, 2, 1.0f, 999, 12, 1.5f) {}

void HunterBow::Equip(std::shared_ptr<Player> &m_Player) {
    m_Player->SetAttack(m_Player->GetAttack() + m_Attack);
    m_Player->SetDefaultAttackCD(m_Player->GetDefaultAttackCD() + this->m_AttackCD);
}

void HunterBow::UnEquip(std::shared_ptr<Player> &m_Player) {
    m_Player->SetAttack(m_Player->GetAttack() - m_Attack);
    m_Player->SetDefaultAttackCD(m_Player->GetDefaultAttackCD() - this->m_AttackCD);
}

void HunterBow::Attack(std::shared_ptr<Map> m_map, std::shared_ptr<Player> &m_Player, Util::Renderer *m_Root) {
    auto projectile = std::make_shared<Projectile>(RESOURCE_DIR"/Weapon/HunterBow/Projectile.png", Util::Input::GetCursorPosition(), 4, m_Player->GetAttack() * m_SkillMultiplier, m_FlightDistance);
    m_map->AddAllObjects(projectile);
    m_map->AddProjectile(projectile);
    m_Root->AddChild(projectile);
}

void HunterBow::Skill(std::shared_ptr<Map> m_map, std::shared_ptr<Player> &m_Player, Util::Renderer* m_Root) {
    PlayWaveSFX();
    auto projectile = std::make_shared<Projectile>(RESOURCE_DIR"/Weapon/HunterBow/SkillProjectile.png", Util::Input::GetCursorPosition(), 4, m_Player->GetAttack() + glm::vec2((int)(m_Player->GetLevel() / 2)), m_FlightDistance, 2);
    m_map->AddAllObjects(projectile);
    m_map->AddProjectile(projectile);
    m_Root->AddChild(projectile);
}