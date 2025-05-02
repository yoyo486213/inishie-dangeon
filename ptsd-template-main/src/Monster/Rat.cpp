#include "Monster/Rat.hpp"
#include "Util/Time.hpp"
#include <random>
#include "Map/InvisibleWall.hpp"
#include "Player.hpp"
#include "Calculation.hpp"
#include "Character.hpp"
#include <iostream>

Rat::Rat() : Monster({RESOURCE_DIR"/Monster/Rat/Rat-B-0.png", RESOURCE_DIR"/Monster/Rat/Rat-B-1.png",
                      RESOURCE_DIR"/Monster/Rat/Rat-F-0.png", RESOURCE_DIR"/Monster/Rat/Rat-F-1.png",
                      RESOURCE_DIR"/Monster/Rat/Rat-L-0.png", RESOURCE_DIR"/Monster/Rat/Rat-L-1.png",
                      RESOURCE_DIR"/Monster/Rat/Rat-R-0.png", RESOURCE_DIR"/Monster/Rat/Rat-R-1.png"},
                      4, 0, glm::vec2{1, 4}, 0, 105, 5, std::vector<int>{-50, 0, 0, 0, 0}, 1, 6, 28.0) {
    this->goalpos = this->GetPosition();
}

void Rat::Move(glm::vec2 displacement, glm::vec2 goal) {
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

    if (this->GetChangeImageCD() <= 0) {
        this->SetChangeImageCD(0.25f);

        if (displacement == glm::vec2{0, 1}) {
            if (m_ImageIndex == 0) { 
                this->ChangeImage(1);
                this->m_ImageIndex = 1;
            }
            else if (m_ImageIndex == 1) {
                this->ChangeImage(0);
                this->m_ImageIndex = 0;
            }
            else {
                this->ChangeImage(0);
                this->m_ImageIndex = 0;
            }
        }
        else if (displacement == glm::vec2{0, -1}) {
            if (m_ImageIndex == 2) { 
                this->ChangeImage(3);
                this->m_ImageIndex = 3;
            }
            else if (m_ImageIndex == 3) {
                this->ChangeImage(2);
                this->m_ImageIndex = 2;
            }
            else {
                this->ChangeImage(2);
                this->m_ImageIndex = 2;
            }
        }
        else if (displacement == glm::vec2{-1, 0}) {
            if (m_ImageIndex == 4) { 
                this->ChangeImage(5);
                this->m_ImageIndex = 5;
            }
            else if (m_ImageIndex == 5) {
                this->ChangeImage(4);
                this->m_ImageIndex = 4;
            }
            else {
                this->ChangeImage(4);
                this->m_ImageIndex = 4;
            }
        }
        else if (displacement == glm::vec2{1, 0}) {
            if (m_ImageIndex == 6) { 
                this->ChangeImage(7);
                this->m_ImageIndex = 7;
            }
            else if (m_ImageIndex == 7) {
                this->ChangeImage(6);
                this->m_ImageIndex = 6;
            }
            else {
                this->ChangeImage(6);
                this->m_ImageIndex = 6;
            }
        }
    }
}

void Rat::Update(std::shared_ptr<Player> &m_Player, std::vector<std::shared_ptr<Character>> AllObjects, std::vector<std::shared_ptr<ICollidable>> AllCollidableObjects, std::vector<std::shared_ptr<InvisibleWall>> m_Invisiblewalls, std::vector<std::shared_ptr<Monster>> m_Monsters) {
    // 初始化隨機數生成器
    std::random_device rd;                   // 真實隨機數生成器
    std::mt19937 engine(rd());               // Mersenne Twister 引擎
    std::uniform_int_distribution<int> distIndex(0, 3);  // 生成 0~3 之間的隨機索引
    std::uniform_int_distribution<int> distValue(1, 11); // 生成 1~11 之間的隨機步長
    std::uniform_int_distribution<int> walkRate(1, 100); // 移動機率
    this->SetChangeImageCD(this->GetChangeImageCD() - Util::Time::GetDeltaTimeMs() / 1000.0f);
    this->SetAttackCD(this->GetAttackCD() - Util::Time::GetDeltaTimeMs() / 1000.0f);
    if (m_Player->GetHP() > 0 && this->GetAttackCD() <= 0 && (this->state == State::Stop || glm::distance(pos, goalpos) == 28)) {
        // 往旁邊走攻擊距離看有沒有碰到玩家
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
                this->SetAttackCD(1.f);
                this->state = State::Stop;
            }
        }
    }
    if (this->state == State::Stop && walkRate(engine) == 1) {
        // 定義四個位移方向，使用 glm::vec2
        glm::vec2 displacements[4] = {
            glm::vec2(0, 1), glm::vec2(0, -1), glm::vec2(1, 0), glm::vec2(-1, 0)
        };
        
        // bool conti = false;
        // while (!conti) {
        // 隨機選擇一個 displacement
        randomDisplacement = displacements[distIndex(engine)];
        
        for (const auto& obj : AllCollidableObjects) {
            auto monster = std::dynamic_pointer_cast<Monster>(obj);
            if (obj->IsCollision(shared_from_this(), Calculation::MulPosition(-randomDisplacement, 14)) && obj != monster && obj != shared_from_this()) {
                return;
            }
        }
        
        for (const auto& monster : m_Monsters) {
            if (monster == shared_from_this()) {
                continue;
            }
            if (Calculation::AddPosition(this->GetPosition(), Calculation::MulPosition(randomDisplacement, 28)) == monster->GetGoalPosition()) {
                return;
            }
        }
        // }

        grids = 0;
        pos = this->GetPosition();
        goalpos = pos + randomDisplacement * 28.f;
        goalgrids = distValue(engine);
        this->state = State::Move;
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
        if (pos == goalpos) {
            this->state = State::Stop;
        }
    }
}