#include "Monster/Worm.hpp"
#include "Util/Time.hpp"
#include <random>
#include "Map/InvisibleWall.hpp"
#include "Map/DestructibleObject.hpp"
#include "Map/Chest.hpp"
#include "Player.hpp"
#include "Calculation.hpp"
#include "Character.hpp"
#include <iostream>
#include <algorithm> // std::max
#include <cmath>    // std::pow

Worm::Worm() : Monster(RESOURCE_DIR"/Monster/Worm.png", 24, 0, glm::vec2{1, 4}, 0, 101, 1, std::vector<int>{0, 0, 0, 0, 0}, 2, 16, 28.0) {
    this->goalpos = this->GetPosition();
}

void Worm::Move(glm::vec2 displacement, glm::vec2 goal) {
    if (((goal.x - pos.x) * displacement.x + (goal.y - pos.y) * displacement.y) > 0) {
        pos += displacement;
        this->SetPosition(this->GetPosition() + displacement);
    }
    else {
        grids++;
        goalpos = Calculation::AddPosition(pos, Calculation::MulPosition(randomDisplacement, 28));
        if (grids >= goalgrids) {
            this->state = State::Stop;
        }
    }
}

void Worm::Update(std::shared_ptr<Player> &m_Player, std::vector<std::shared_ptr<Character>> AllObjects, std::vector<std::shared_ptr<ICollidable>> AllCollidableObjects, std::vector<std::shared_ptr<InvisibleWall>> m_Invisiblewalls, std::vector<std::shared_ptr<Monster>> m_Monsters) {
    // 初始化隨機數生成器
    std::random_device rd;                   // 真實隨機數生成器
    std::mt19937 engine(rd());               // Mersenne Twister 引擎
    std::uniform_int_distribution<int> distIndex(0, 7);  // 生成 0~3 之間的隨機索引
    std::uniform_int_distribution<int> distValue(1, 1); // 生成 1~11 之間的隨機步長
    std::uniform_int_distribution<int> walkRate(1, 60); // 移動機率
    this->SetAttackCD(this->GetAttackCD() - Util::Time::GetDeltaTimeMs() / 1000.0f);
    if (m_Player->GetHP() > 0 && (this->state == State::Stop || static_cast<int>(glm::distance(pos, goalpos)) == 28)) {
        // 往旁邊走攻擊距離看有沒有碰到玩家
        const std::vector<glm::vec2> directions = {
            {0, 1}, {0, -1}, {-1, 0}, {1, 0}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}
        };
        for (const auto& dir : directions) {
            if (this->IsCollision(m_Player, dir * m_TrackRange)) {
                if (this->GetAttackCD() <= 0) {
                    std::uniform_real_distribution<double> hitrate(0, 100.0);
                    if (hitrate(engine) < m_Player->GetBlockrate()) {
                        std::cout << "Block!" << std::endl;
                        break;
                    }
                    if (hitrate(engine) > m_Hitrate / ((m_Player->GetDodgerate() + 100) / 100.0)) {
                        std::cout << "Miss!" << std::endl;
                        break;
                    }
                    m_Player->TakeDamage(Calculation::CalcuAttack(m_Attack, 0));
                    this->SetAttackCD(1.f);
                }
            }
        }
        if (this->IsCollision(m_Player, randomDisplacement)) {
            return;
        }
    }
    if (this->state == State::Stop) {
        const std::vector<glm::vec2> directions = {
            {0, 1}, {0, -1}, {-1, 0}, {1, 0}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}, {0, 0}
        };
        
        if (glm::distance(m_Player->GetPosition(), this->GetPosition()) <= 84) {
            this->following = true;
        }
        if (following) {
            int mindis = 99999;
            for (const auto& dir : directions) {
                bool collidable = false;
                if (this->IsCollision(m_Player, Calculation::MulPosition(dir, 14))) {
                    collidable = true;
                }
                for (const auto& obj : AllCollidableObjects) {
                    if (obj->IsCollision(shared_from_this(), Calculation::MulPosition(-dir, 14)) && obj != shared_from_this()) {
                        collidable = true;
                    }
                }
                bool conti = true;
                for (const auto& monster : m_Monsters) {
                    if (Calculation::AddPosition(pos, Calculation::MulPosition(dir, 28)) == monster->GetGoalPosition()) {
                        conti = false;
                    }
                }
                if (!collidable && conti && static_cast<int>(glm::distance(m_Player->GetPosition(), this->GetPosition() + Calculation::MulPosition(dir, 28))) < mindis) {
                    mindis = static_cast<int>(glm::distance(m_Player->GetPosition(), this->GetPosition() + Calculation::MulPosition(dir, 28)));
                    pos = this->GetPosition();
                    randomDisplacement = dir;
                    goalpos = Calculation::AddPosition(pos, Calculation::MulPosition(randomDisplacement, 28));
                    grids = 0;
                    goalgrids = 1;
                    state = State::Move;
                }
            }
        }

        // 隨機選擇一個方向
        if (walkRate(engine) == 1 && this->state == State::Stop) {
            // 定義四個位移方向，使用 glm::vec2
            glm::vec2 displacements[8] = {
                glm::vec2(0, 1), glm::vec2(0, -1), glm::vec2(1, 0), glm::vec2(-1, 0), glm::vec2(1, 1), glm::vec2(1, -1), glm::vec2(-1, 1), glm::vec2(-1, -1)
            };
            // 隨機選擇一個 displacement
            randomDisplacement = displacements[distIndex(engine)];
            grids = 0;
            pos = this->GetPosition();
            goalpos = Calculation::AddPosition(pos, Calculation::MulPosition(randomDisplacement, 28));
            goalgrids = distValue(engine);
            this->state = State::Move;
        }
    }
    if (this->state == State::Move) {
        for (const auto& obj : AllCollidableObjects) {
            if (obj->IsCollision(shared_from_this(), -randomDisplacement) && obj != shared_from_this()) {
                this->state = State::Stop;
                return;
            }
        }
        
        if (this->IsCollision(m_Player, randomDisplacement) && static_cast<int>(glm::distance(pos, goalpos)) == 28) {
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
        for (const auto& obj : AllCollidableObjects) {
            if (obj->IsCollision(m_Player, -randomDisplacement)) {
                this->state = State::Move;
                return;
            }   
        }
        
        for (const auto& obj : AllObjects) {
            obj->SetPosition(obj->GetPosition() - randomDisplacement);
        }
        for (const auto& invisiblewall : m_Invisiblewalls) {
            invisiblewall->SetPosition(invisiblewall->GetPosition() - randomDisplacement);
        }
        for (const auto& monster : m_Monsters) {
            if (monster != shared_from_this()) {
                monster->SetPosition(monster->GetPosition() - randomDisplacement);
            }
        }
        pos += randomDisplacement;
        if (std::abs(pos.x - goalpos.x) < 0.0001f && std::abs(pos.y - goalpos.y) < 0.0001f) {
            this->state = State::Stop;
        }
    }
}