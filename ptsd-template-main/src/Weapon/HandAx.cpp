#include "Weapon/HandAx.hpp"
#include "Weapon/Projectile.hpp"
#include "Util/Input.hpp"
#include "Player.hpp"
#include "Map/Map.hpp"
#include "App.hpp"

HandAx::HandAx()
    : Weapon(RESOURCE_DIR"/Weapon/HandAx.png", glm::vec2{5, 10}, 3, 1.0f, 4, 10, 1.0f) {}

void HandAx::Equip(std::shared_ptr<Player> &m_Player) {
    m_Player->SetAttack(m_Player->GetAttack() + m_Attack);
    m_Player->SetDefaultAttackCD(m_Player->GetDefaultAttackCD() + this->m_AttackCD);
}

void HandAx::UnEquip(std::shared_ptr<Player> &m_Player) {
    m_Player->SetAttack(m_Player->GetAttack() - m_Attack);
    m_Player->SetDefaultAttackCD(m_Player->GetDefaultAttackCD() - this->m_AttackCD);
}

void HandAx::Skill(std::shared_ptr<Map> m_map, std::shared_ptr<Player> &m_Player, Util::Renderer *m_Root) {
    PlayWaveSFX();
    auto projectile = std::make_shared<Projectile>(RESOURCE_DIR"/Weapon/HandAx.png", Util::Input::GetCursorPosition(), 3, m_Player->GetAttack() * m_SkillMultiplier, m_FlightDistance, 0, 1.0f, glm::vec2({0, 0}), ProjectileBehaviorType::AxeSpin, true, false);
    m_map->AddAllObjects(projectile);
    m_map->AddProjectile(projectile);
    m_Root->AddChild(projectile);
}