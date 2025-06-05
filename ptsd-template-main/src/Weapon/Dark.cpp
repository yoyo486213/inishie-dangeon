#include "Weapon/Dark.hpp"
#include "Weapon/Projectile.hpp"
#include "Util/Input.hpp"
#include "Player.hpp"
#include "Map/Map.hpp"
#include "App.hpp"
#include <cmath>

Dark::Dark()
    : Weapon(RESOURCE_DIR"/Weapon/Dark.png", glm::vec2{4, 7}, 1, 1.2f, 3, 7, 0.6f) {}

void Dark::Equip(std::shared_ptr<Player> &m_Player) {
    m_Player->SetAttack(m_Player->GetAttack() + m_Attack);
    m_Player->SetDefaultAttackCD(m_Player->GetDefaultAttackCD() + this->m_AttackCD);
}

void Dark::UnEquip(std::shared_ptr<Player> &m_Player) {
    m_Player->SetAttack(m_Player->GetAttack() - m_Attack);
    m_Player->SetDefaultAttackCD(m_Player->GetDefaultAttackCD() - this->m_AttackCD);
}

void Dark::Skill(std::shared_ptr<Map> m_map, std::shared_ptr<Player> &m_Player, Util::Renderer *m_Root) {
    glm::vec2 center = {0.0f, 0.0f};  // 可以換成角色座標

    float radius = 28.0f;  // 繞中心距離
    float angleOffset = glm::radians(120.0f);  // 每顆間隔 120 度

    for (int i = 0; i < 3; ++i) {
        float angle = i * angleOffset;

        glm::vec2 pos = center + glm::vec2(cos(angle), sin(angle)) * radius;
        std::cout << "Projectile position: " << pos.x << ", " << pos.y << std::endl;

        auto projectile = std::make_shared<Projectile>(
            RESOURCE_DIR"/Weapon/Dark.png",                      // 貼圖
            glm::vec2({0, 0}),                             // 無方向
            0.0f,                                        // 不移動
            glm::vec2({5, 10}),                            // 傷害
            0,                                           // 飛行距離不需要
            2,                                         // 技能範圍
            5.0f,                                        // 停留 5 秒
            pos,                                         // 起始位置
            ProjectileBehaviorType::OrbitingBoomerang,  // 繞圈類型
            true,                                        // 可碰撞
            false                                        // 不會提前消失
        );

        // 儲存額外角度參數（下方補上計算）
        // projectile->SetExtra("angle", angle);  // 請確保你有支援附加變數的方法，或用 map 裝 custom data

        m_map->AddAllObjects(projectile);
        m_map->AddProjectile(projectile);
        m_Root->AddChild(projectile);
    }
}