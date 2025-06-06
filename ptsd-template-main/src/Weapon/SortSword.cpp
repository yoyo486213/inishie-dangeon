#include "Weapon/SortSword.hpp"
#include "Weapon/Projectile.hpp"
#include "Player.hpp"
#include "Map/Map.hpp"
#include "App.hpp"

SortSword::SortSword(std::shared_ptr<Map> m_map, std::shared_ptr<Player> m_Player, Util::Renderer *m_Root)
    : Weapon(RESOURCE_DIR"/Weapon/SortSword/SortSword.png", glm::vec2{4, 7}, 1, 1.2f, 3, 7, 0.6f, m_map, m_Player, m_Root) {}

void SortSword::Equip() {
    m_Player->SetAttack(m_Player->GetAttack() + glm::vec2{1000, 2000});
    m_Player->SetAttackCD(m_Player->GetAttackCD() + this->m_AttackCD);
    Use_time = std::chrono::high_resolution_clock::now();
}

void SortSword::UnEquip() {
    m_Player->SetAttack(m_Player->GetAttack() - glm::vec2{1000, 2000});
    m_Player->SetAttackCD(m_Player->GetAttackCD() - this->m_AttackCD);
}

void SortSword::Skill(std::shared_ptr<Map> m_map, Util::Renderer *m_Root) {
    auto projectile = std::make_shared<Projectile>(RESOURCE_DIR"/Weapon/SortSword/Projectile.png", 2, m_Attack * m_SkillMultiplier, m_SkillRange);
    m_map->AddProjectile(projectile);
    m_Root->AddChild(projectile);
}