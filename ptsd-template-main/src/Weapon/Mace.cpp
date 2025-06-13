#include "Weapon/Mace.hpp"
#include "Weapon/Projectile.hpp"
#include "Util/Input.hpp"
#include "Player.hpp"
#include "Map/Map.hpp"
#include "App.hpp"
#include <iostream>
#include <algorithm>

Mace::Mace()
    : Weapon(RESOURCE_DIR"/Weapon/Mace/Mace.png", glm::vec2{5, 7}, 1, 0.0f, 0, 20, 5.0f) {}

void Mace::Equip(std::shared_ptr<Player> &m_Player) {
    m_Player->SetAttack(m_Player->GetAttack() + m_Attack);
    m_Player->SetDefaultAttackCD(m_Player->GetDefaultAttackCD() + this->m_AttackCD);
}

void Mace::UnEquip(std::shared_ptr<Player> &m_Player) {
    m_Player->SetAttack(m_Player->GetAttack() - m_Attack);
    m_Player->SetDefaultAttackCD(m_Player->GetDefaultAttackCD() - this->m_AttackCD);
}

void Mace::Skill(std::shared_ptr<Map> m_map, std::shared_ptr<Player> &m_Player, Util::Renderer *m_Root) {
    PlayWaveSFX();
    auto res = m_Player->GetResistance();
    int extra = std::min(50, (int)((m_Player->GetAttack().x + m_Player->GetAttack().y) / 4) + 20);
    res[4] += extra;
    m_Player->SetResistance(res);

    auto projectile = std::make_shared<Projectile>(RESOURCE_DIR"/Weapon/Mace/Effects-1.png", glm::vec2(999, 0), 0, glm::vec2(0, 0), m_FlightDistance, 0, 10.0f, m_Player->GetPosition(), ProjectileBehaviorType::DefenseEffects, false);
    m_map->AddProjectile(projectile);
    m_Root->AddChild(projectile);
}