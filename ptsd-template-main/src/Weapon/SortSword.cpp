#include "Weapon/SortSword.hpp"
#include "Weapon/Projectile.hpp"
#include "Util/Input.hpp"
#include "Player.hpp"
#include "Map/Map.hpp"
#include "App.hpp"

SortSword::SortSword(std::shared_ptr<Map> m_map, Util::Renderer *m_Root)
    : Weapon(RESOURCE_DIR"/Weapon/SortSword/SortSword.png", glm::vec2{4, 7}, 1, 1.2f, 3, 7, 0.6f, m_map, m_Root) {}

void SortSword::Equip(std::shared_ptr<Player> &m_Player) {
    m_Player->SetAttack(m_Player->GetAttack() + m_Attack);
    m_Player->SetDefaultAttackCD(m_Player->GetDefaultAttackCD() + this->m_AttackCD);
}

void SortSword::UnEquip(std::shared_ptr<Player> &m_Player) {
    m_Player->SetAttack(m_Player->GetAttack() - m_Attack);
    m_Player->SetDefaultAttackCD(m_Player->GetDefaultAttackCD() - this->m_AttackCD);
}

void SortSword::Skill(std::shared_ptr<Map> m_map, std::shared_ptr<Player> &m_Player, Util::Renderer *m_Root) {
    auto projectile = std::make_shared<Projectile>(RESOURCE_DIR"/Weapon/SortSword/Projectile.png", Util::Input::GetCursorPosition(), 3, m_Player->GetAttack() * m_SkillMultiplier, m_FlightDistance);
    m_map->AddAllObjects(projectile);
    m_map->AddProjectile(projectile);
    m_Root->AddChild(projectile);
}