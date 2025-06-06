#include "Weapon/Dagger.hpp"
#include "Weapon/Projectile.hpp"
#include "Util/Input.hpp"
#include "Player.hpp"
#include "Map/Map.hpp"
#include "App.hpp"

Dagger::Dagger()
    : Weapon(RESOURCE_DIR"/Weapon/Dagger/Dagger.png", glm::vec2{1, 4}, 0, 0.8f, 4, 5, 0.3f) {}

void Dagger::Equip(std::shared_ptr<Player> &m_Player) {
    m_Player->SetAttack(m_Player->GetAttack() + m_Attack);
    m_Player->SetDefaultAttackCD(m_Player->GetDefaultAttackCD() + this->m_AttackCD);
}

void Dagger::UnEquip(std::shared_ptr<Player> &m_Player) {
    m_Player->SetAttack(m_Player->GetAttack() - m_Attack);
    m_Player->SetDefaultAttackCD(m_Player->GetDefaultAttackCD() - this->m_AttackCD);
}

void Dagger::Skill(std::shared_ptr<Map> m_map, std::shared_ptr<Player> &m_Player, Util::Renderer *m_Root) {
    glm::vec2 cursorPos = Util::Input::GetCursorPosition();

    std::default_random_engine engine(std::random_device{}());
    std::uniform_real_distribution<float> angleOffset(-5.0f, 5.0f); // ±15度的散射角度

    for (int i = 0; i < 3; ++i) {
        glm::vec2 direction = glm::normalize(cursorPos);

        float angle = glm::radians(angleOffset(engine));
        glm::vec2 rotatedDir = {
            direction.x * cos(angle) - direction.y * sin(angle),
            direction.x * sin(angle) + direction.y * cos(angle)
        };

        glm::vec2 finalTarget = rotatedDir * 300.0f; // 射出目標點（300為距離）

        auto projectile = std::make_shared<Projectile>(
            RESOURCE_DIR"/Weapon/Dagger/Projectile.png", 
            finalTarget, 
            4, 
            (m_Player->GetAttack() + glm::vec2(m_Player->GetLevel() / 2)) * 0.8f,
            m_FlightDistance
        );

        m_map->AddAllObjects(projectile);
        m_map->AddProjectile(projectile);
        m_Root->AddChild(projectile);
    }
}