#include "Weapon/Dark.hpp"
#include "Weapon/Projectile.hpp"
#include "Util/Input.hpp"
#include "Player.hpp"
#include "Map/Map.hpp"
#include "App.hpp"
#include <cmath>

Dark::Dark()
    : Weapon(RESOURCE_DIR"/Weapon/Dark.png", glm::vec2{2, 8}, 0, 1.2f, 0, 0, 10.0f) {}

void Dark::Equip(std::shared_ptr<Player> &m_Player) {
    m_Player->SetAttack(m_Player->GetAttack() + m_Attack);
    m_Player->SetDefaultAttackCD(m_Player->GetDefaultAttackCD() + this->m_AttackCD);
}

void Dark::UnEquip(std::shared_ptr<Player> &m_Player) {
    m_Player->SetAttack(m_Player->GetAttack() - m_Attack);
    m_Player->SetDefaultAttackCD(m_Player->GetDefaultAttackCD() - this->m_AttackCD);
}

void Dark::Skill(std::shared_ptr<Map> m_map, std::shared_ptr<Player> &m_Player, Util::Renderer *m_Root) {
    glm::vec2 center = m_Player->GetPosition();

    for (int i = 0; i < 3; ++i) {
        float baseAngle = glm::radians(120.0f * i);
        float randomPhase = static_cast<float>(rand()) / RAND_MAX * glm::two_pi<float>();

        auto projectile = std::make_shared<Projectile>(
            RESOURCE_DIR"/Weapon/Dark.png",
            glm::vec2({999, 999}),
            0.0f,
            m_Player->GetAttack() + glm::vec2(m_Player->GetLevel() / 2),
            0,
            0,
            15.0f,
            center,
            ProjectileBehaviorType::FreeOrbiting,
            true,
            false
        );

        projectile->SetOrbitAngle(baseAngle);        // 初始旋轉角度
        projectile->SetOrbitPhaseOffset(randomPhase);  // 讓每顆的忽近忽遠有偏移


        m_map->AddProjectile(projectile);
        m_Root->AddChild(projectile);
    }
}