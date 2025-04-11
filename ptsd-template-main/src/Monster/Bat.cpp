#include "Monster/Bat.hpp"
#include "Util/Time.hpp"
#include <random>
#include "Map/InvisibleWall.hpp"
#include "Player.hpp"
#include "Calculation.hpp"
#include "Character.hpp"
#include <iostream>

Bat::Bat() : Monster(RESOURCE_DIR"/Monster/Bat.png", 8, 0, glm::vec2{2, 5}, 0, 125, 25, std::vector<int>{0, 0, 0, 0, 0}, 2, 12, 28.0) {}

bool Bat::IsCollision(const std::shared_ptr<Character> &other, glm::vec2 displacement) {
    glm::vec2 thisSize = this->GetScaledSize();
    glm::vec2 otherSize = other->GetScaledSize();

    glm::vec2 thisPos = this->GetPosition() + displacement - glm::vec2({thisSize.x / 2.0, thisSize.y / 2.0});
    glm::vec2 otherPos = other->GetPosition() - glm::vec2({otherSize.x / 2.0, otherSize.y / 2.0});

    bool xOverlap = thisPos.x + thisSize.x > otherPos.x && otherPos.x + otherSize.x > thisPos.x;
    bool yOverlap = thisPos.y + thisSize.y > otherPos.y && otherPos.y + otherSize.y > thisPos.y;

    return xOverlap && yOverlap && this->GetVisibility();
}

void Bat::Move(glm::vec2 displacement, glm::vec2 goal) {
    if (((goal[0] - pos.x) * displacement[0] + (goal[1] - pos.y) * displacement[1]) > 0) {
        pos += displacement;
        this->SetPosition(this->GetPosition() + displacement);
    }
    else {
        grids++;
        goalpos = pos + randomDisplacement * 28.f;
        if (grids >= goalgrids) {
            this->state = State::Stop;
        }
    }
}

void Bat::Update( std::shared_ptr<Player> &m_Player, std::vector<std::shared_ptr<Character>> AllObjects, std::vector<std::shared_ptr<ICollidable>> AllCollidableObjects, std::vector<std::shared_ptr<InvisibleWall>> m_Invisiblewalls) {
    // 初始化隨機數生成器
    std::random_device rd;                   // 真實隨機數生成器
    std::mt19937 engine(rd());               // Mersenne Twister 引擎
    std::uniform_int_distribution<int> distIndex(0, 3);  // 生成 0~3 之間的隨機索引
    std::uniform_int_distribution<int> distValue(1, 11); // 生成 1~11 之間的隨機步長
    std::uniform_int_distribution<int> walkBate(1, 100); // 移動機率
    this->SetAttackCD(this->GetAttackCD() - Util::Time::GetDeltaTimeMs() / 1000.0f);
    if (m_Player->GetHP() > 0 && this->GetAttackCD() <= 0 && (this->state == State::Stop || glm::distance(pos, goalpos) == 28)) {
        // 往旁邊走攻擊距離看有沒有碰到玩家
        const std::vector<glm::vec2> directions = {
            {0, 1}, {0, -1}, {-1, 0}, {1, 0}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}
        };
        for (const auto& dir : directions) {
            if (this->IsCollision(m_Player, dir * m_TrackRange)) {
                std::uniform_real_distribution<double> hitBate(0, 100.0);
                if (hitBate(engine) < m_Player->GetBlockrate()) {
                    std::cout << "Block!" << std::endl;
                    break;
                }
                if (hitBate(engine) > m_Hitrate / ((m_Player->GetDodgerate() + 100) / 100.0)) {
                    std::cout << "Miss!" << std::endl;
                    break;
                }
                m_Player->TakeDamage(Calculation::CalcuAttack(m_Attack, 0));
                this->SetAttackCD(1.f);
            }
        }
    }
    if (this->state == State::Stop && walkBate(engine) == 1) {
        // 定義四個位移方向，使用 glm::vec2
        glm::vec2 displacements[4] = {
            glm::vec2(0, 1), glm::vec2(0, -1), glm::vec2(1, 0), glm::vec2(-1, 0)
        };
        // 隨機選擇一個 displacement
        randomDisplacement = displacements[distIndex(engine)];
        grids = 0;
        pos = this->GetPosition();
        goalpos = pos + randomDisplacement * 28.f;
        goalgrids = distValue(engine);
        this->state = State::Move;
    }
    if (this->state == State::Move) {
        for (const auto& obj : AllCollidableObjects) {
            if (obj->IsCollision(shared_from_this(), -randomDisplacement) && obj != shared_from_this()) {
                this->state = State::Stop;
                return;
            }
        }
        if (this->IsCollision(m_Player, randomDisplacement) && glm::distance(pos, goalpos) == 28) {
            this->state = State::Stop;
            return;
        }
        if (this->IsCollision(m_Player, randomDisplacement) && static_cast<int>(glm::distance(pos, goalpos)) % 28 != 0) {
            this->state = State::MoveMap;
            return;
        }

        Move(randomDisplacement, goalpos);
    }
    if (this->state == State::MoveMap) {
        for (const auto& obj : AllObjects) {
            obj->SetPosition(obj->GetPosition() - randomDisplacement);
        }
        for (const auto& invisiblewall : m_Invisiblewalls) {
            invisiblewall->SetPosition(invisiblewall->GetPosition() - randomDisplacement);
        }
        pos += randomDisplacement;
        if (pos == goalpos) {
            this->state = State::Stop;
        }
    }
}