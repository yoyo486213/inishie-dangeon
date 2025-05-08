#include "Monster/Slime.hpp"
#include "Util/Time.hpp"
#include <random>
#include "Map/InvisibleWall.hpp"
#include "Player.hpp"
#include "Calculation.hpp"
#include "Character.hpp"
#include <iostream>

Slime::Slime() : Monster({RESOURCE_DIR"/Monster/Slime/Slime-0.png", RESOURCE_DIR"/Monster/Slime/Slime-1.png"}, 
                          40, 0, glm::vec2{2, 5}, 0, 102, 2, std::vector<int>{0, 0, -50, 0, 0}, 10, 20, 28.0) {
}

void Slime::Move(glm::vec2 displacement, glm::vec2 goal, std::vector<std::shared_ptr<Monster>> m_Monsters) {
    if (!Calculation::Equal(pos, goal)) {
        pos += displacement;
        this->SetPosition(this->GetPosition() + displacement);
    }
    else {
        grids++;
        if (grids >= goalgrids) {
            this->state = State::Stop;
        }
        else {
            bool conti = true;
            for (const auto& monster : m_Monsters) {
                if (monster == shared_from_this()) {
                    continue;
                }
                if (Calculation::Equal(Calculation::AddPosition(this->GetPosition(), Calculation::MulPosition(randomDisplacement, 56)), monster->GetGoalPosition())) {
                    conti = false;
                }
            }
            if (conti) {
                goalpos = Calculation::AddPosition(pos, Calculation::MulPosition(randomDisplacement, 56));
            }
        }
    }

    if (this->GetChangeImageCD() <= 0) {
        this->SetChangeImageCD(0.25f);

        if (m_ImageIndex == 0) { 
            this->ChangeImage(1);
            this->m_ImageIndex = 1;
        }
        else {
            this->ChangeImage(0);
            this->m_ImageIndex = 0;
        }
    }
}

void Slime::Update(std::shared_ptr<Player> &m_Player, std::vector<std::shared_ptr<Character>> AllObjects, std::vector<std::shared_ptr<ICollidable>> AllCollidableObjects, std::vector<std::shared_ptr<InvisibleWall>> m_Invisiblewalls, std::vector<std::shared_ptr<Monster>> m_Monsters) {
    // 初始化隨機數生成器
    std::random_device rd;                   // 真實隨機數生成器
    std::mt19937 engine(rd());               // Mersenne Twister 引擎
    std::uniform_int_distribution<int> distIndex(0, 7);  // 生成 0~3 之間的隨機索引
    std::uniform_int_distribution<int> distValue(1, 1); // 生成 1~11 之間的隨機步長
    std::uniform_int_distribution<int> walkRate(1, 1000); // 移動機率
    std::uniform_int_distribution<int> followRate(1, 100); // 移動機率
    this->SetChangeImageCD(this->GetChangeImageCD() - Util::Time::GetDeltaTimeMs() / 1000.0f);
    this->SetAttackCD(this->GetAttackCD() - Util::Time::GetDeltaTimeMs() / 1000.0f);
    if (m_Player->GetHP() > 0 && this->GetAttackCD() <= 0 && this->state == State::Stop) {
        // 往旁邊走攻擊距離看有沒有碰到玩家
        this->walkRateValue = 5;
        const std::vector<glm::vec2> directions = {
            {0, 1}, {0, -1}, {-1, 0}, {1, 0}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}
        };
        for (const auto& dir : directions) {
            if (this->IsCollision(m_Player, dir * m_TrackRange)) {
                std::uniform_real_distribution<double> hitrate(0, 100.0);
                int rate = hitrate(engine);
                if (rate < m_Player->GetBlockrate()) {
                    std::cout << "Block!" << std::endl;
                    break;
                }
                if (rate > m_Hitrate / ((m_Player->GetDodgerate() + 100) / 100.0)) {
                    std::cout << "Miss!" << std::endl;
                    break;
                }
                m_Player->TakeDamage(Calculation::CalcuAttack(m_Attack, 0));
                this->SetAttackCD(0.5f);
            }
        }
    }
    if (this->state == State::Stop && walkRate(engine) <= this->walkRateValue) {
        // 定義四個位移方向，使用 glm::vec2
        this->walkRateValue = 700;

        if (glm::distance(m_Player->GetPosition(), this->GetPosition()) <= 84 && followRate(engine) <= 90) {
            const std::vector<glm::vec2> directions = {
                {0, 1}, {0, -1}, {-1, 0}, {1, 0}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}, {0, 0}
            };
            int mindis = 99999;
            for (const auto& dir : directions) {
                bool collidable = false;
                if (this->IsCollision(m_Player, Calculation::MulPosition(dir, 14))) {
                    collidable = true;
                }
                for (const auto& obj : AllCollidableObjects) {
                    auto monster = std::dynamic_pointer_cast<Monster>(obj);
                    if (obj->IsCollision(shared_from_this(), Calculation::MulPosition(-dir, 14)) && obj != monster && obj != shared_from_this()) {
                        collidable = true;
                    }
                }
                for (const auto& monster : m_Monsters) {
                    if (monster == shared_from_this()) {
                        continue;
                    }
                    if (Calculation::Equal(Calculation::AddPosition(this->GetPosition(), Calculation::MulPosition(dir, 28)), monster->GetGoalPosition())) {
                        collidable = true;
                    }
                }
                if (!collidable && static_cast<int>(glm::distance(m_Player->GetPosition(), this->GetPosition() + Calculation::MulPosition(dir, 28))) < mindis) {
                    mindis = static_cast<int>(glm::distance(m_Player->GetPosition(), this->GetPosition() + Calculation::MulPosition(dir, 28)));
                    randomDisplacement = dir;
                }
            }

            if (mindis != 99999) {
                pos = this->GetPosition();
                goalpos = Calculation::AddPosition(pos, Calculation::MulPosition(randomDisplacement, 56));
                grids = 0;
                goalgrids = 1;
                state = State::Move;
            }
        }
        
        if (this->state == State::Stop) {
            glm::vec2 displacements[8] = {
                glm::vec2(0, 1), glm::vec2(0, -1), glm::vec2(1, 0), glm::vec2(-1, 0), glm::vec2(1, 1), glm::vec2(1, -1), glm::vec2(-1, 1), glm::vec2(-1, -1)
            };

            // 隨機選擇一個 displacement
            randomDisplacement = displacements[distIndex(engine)] * 0.5f;

            bool conti = true;
            for (const auto& obj : AllCollidableObjects) {
                auto monster = std::dynamic_pointer_cast<Monster>(obj);
                if (obj->IsCollision(shared_from_this(), Calculation::MulPosition(-randomDisplacement, 28)) && obj != monster && obj != shared_from_this()) {
                    conti = false;
                }
            }
            
            for (const auto& monster : m_Monsters) {
                if (monster == shared_from_this()) {
                    continue;
                }
                if (Calculation::Equal(Calculation::AddPosition(this->GetPosition(), Calculation::MulPosition(randomDisplacement, 56)), monster->GetGoalPosition())) {
                    conti = false;
                }
            }

            if (conti) {
                grids = 0;
                pos = this->GetPosition();
                goalpos = pos + randomDisplacement * 56.f;
                goalgrids = distValue(engine);
                this->state = State::Move;
            }
        }

        if (this->state == State::Stop) {
            this->SetGoalPosition(this->GetPosition());
        }
    }
    if (this->state == State::Move) {
        for (const auto& obj : AllCollidableObjects) {
            auto monster = std::dynamic_pointer_cast<Monster>(obj);
            if (obj->IsCollision(shared_from_this(), -randomDisplacement) && obj != monster && obj != shared_from_this()) {
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

        Move(randomDisplacement, goalpos, m_Monsters);
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
        if (pos == goalpos) {
            this->state = State::Stop;
            this->SetGoalPosition(this->GetPosition());
        }
    }
}