#include "Weapon/SortSword.hpp"
#include "Weapon/Projectile.hpp"
#include "Player.hpp"
#include "Map/Map.hpp"
#include "App.hpp"

SortSword::SortSword()
    : Weapon(RESOURCE_DIR"/Weapon/SortSword/SortSword.png", glm::vec2{4, 7}, 1, 1.2f, 3, 7, 0.6f) {}

void SortSword::Equip(std::shared_ptr<Player> &m_Player) {
    m_Player->SetAttack(m_Player->GetAttack() + glm::vec2{1000, 2000});
    m_Player->SetAttackCD(m_Player->GetAttackCD() + this->m_AttackCD);
}

void SortSword::UnEquip(std::shared_ptr<Player> &m_Player) {
    m_Player->SetAttack(m_Player->GetAttack() - glm::vec2{1000, 2000});
    m_Player->SetAttackCD(m_Player->GetAttackCD() - this->m_AttackCD);
}

void SortSword::Skill(std::shared_ptr<Map> m_map, Util::Renderer *m_Root) {
    auto projectile = std::make_shared<Projectile>(RESOURCE_DIR"/Weapon/SortSword/Projectile.png", 2, m_Attack * m_SkillMultiplier, m_SkillRange);
    m_map->AddProjectile(projectile);
    m_Root->AddChild(projectile);
}