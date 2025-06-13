#include "Monster/Skeleton.hpp"
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

Skeleton::Skeleton() : Monster({RESOURCE_DIR"/Monster/Skeleton/Skeleton-B-0.png", RESOURCE_DIR"/Monster/Skeleton/Skeleton-B-1.png",
                                RESOURCE_DIR"/Monster/Skeleton/Skeleton-F-0.png", RESOURCE_DIR"/Monster/Skeleton/Skeleton-F-1.png",
                                RESOURCE_DIR"/Monster/Skeleton/Skeleton-L-0.png", RESOURCE_DIR"/Monster/Skeleton/Skeleton-L-1.png",
                                RESOURCE_DIR"/Monster/Skeleton/Skeleton-R-0.png", RESOURCE_DIR"/Monster/Skeleton/Skeleton-R-1.png"}, 
                                23, 0, glm::vec2{5, 8}, 3, 103, 3, std::vector<int>{40, 0, 0, 0, 0}, 3, 24, 28.0) {
}

void Skeleton::Move(glm::vec2 displacement, glm::vec2 goal, std::vector<std::shared_ptr<Monster>> m_Monsters) {
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
                if (Calculation::Equal(Calculation::AddPosition(this->GetPosition(), Calculation::MulPosition(randomDisplacement, 28)), monster->GetGoalPosition())) {
                    conti = false;
                }
            }
            if (conti) {
                goalpos = Calculation::AddPosition(pos, Calculation::MulPosition(randomDisplacement, 28));
            }
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
        else if (displacement == glm::vec2{-1, 0} || displacement == glm::vec2{-1, 1} || displacement == glm::vec2{-1, -1}) {
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
        else if (displacement == glm::vec2{1, 0} || displacement == glm::vec2{1, 1} || displacement == glm::vec2{1, -1}) {
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

void Skeleton::Update(std::shared_ptr<Player> &m_Player, std::vector<std::shared_ptr<Character>> AllObjects, std::vector<std::shared_ptr<ICollidable>> AllCollidableObjects, std::vector<std::shared_ptr<InvisibleWall>> m_Invisiblewalls, std::vector<std::shared_ptr<Monster>> m_Monsters) {
    // 初始化隨機數生成器
    std::random_device rd;                   // 真實隨機數生成器
    std::mt19937 engine(rd());               // Mersenne Twister 引擎
    std::uniform_int_distribution<int> distIndex(0, 7);  // 生成 0~3 之間的隨機索引
    std::uniform_int_distribution<int> distValue(1, 11); // 生成 1~11 之間的隨機步長
    std::uniform_int_distribution<int> walkRate(1, 60); // 移動機率
    std::uniform_int_distribution<int> revivalRate(1, 50);
    this->SetChangeImageCD(this->GetChangeImageCD() - Util::Time::GetDeltaTimeMs() / 1000.0f);
    this->SetAttackCD(this->GetAttackCD() - Util::Time::GetDeltaTimeMs() / 1000.0f);
    // 復活
    if (m_revivalCD <= 0) {
        m_revivalCD = 3.f;
        revival = false;
        this->Restore_HP(23);
        this->state = State::Stop;
        this->SetAttackCD(1.f);
        this->SetVisible(true);
    }
    if (revival) {
        this->m_revivalCD -= Util::Time::GetDeltaTimeMs() / 1000.0f;
        return;
    }
    if (this->GetHP() <= 0 && !revivaled && revivalRate(engine) == 1) {
        revival = true;
        revivaled = true;
        this->state = State::Stop;
        return;
    }

    if (this->GetHP() > 0 && m_Player->GetHP() > 0 && (this->state == State::Stop || static_cast<int>(glm::distance(pos, goalpos)) == 28)) {
        // 往旁邊走攻擊距離看有沒有碰到玩家
        const std::vector<glm::vec2> directions = {
            {0, 1}, {0, -1}, {-1, 0}, {1, 0}
        };
        for (const auto& dir : directions) {
            if (this->IsCollision(m_Player, dir * m_TrackRange)) {
                if (this->GetAttackCD() <= 0) {
                    std::uniform_real_distribution<double> hitrate(0, 100.0);
                    int rate = hitrate(engine);
                    if (rate < m_Player->GetBlockrate()) {
                        // std::cout << "Block!" << std::endl;
                        m_Player->PlayBlockSFX();
                        break;
                    }
                    if (rate > m_Hitrate / ((m_Player->GetDodgerate() + 100) / 100.0)) {
                        // std::cout << "Miss!" << std::endl;
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
        
        if (glm::distance(m_Player->GetPosition(), this->GetPosition()) <= 168) {
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
                goalpos = Calculation::AddPosition(pos, Calculation::MulPosition(randomDisplacement, 28));
                grids = 0;
                goalgrids = 1;
                state = State::Move;
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
            
            bool conti = true;
            if (this->IsCollision(m_Player, Calculation::MulPosition(randomDisplacement, 14))) {
                conti = false;
            }
            for (const auto& obj : AllCollidableObjects) {
                auto monster = std::dynamic_pointer_cast<Monster>(obj);
                if (obj->IsCollision(shared_from_this(), Calculation::MulPosition(-randomDisplacement, 14)) && obj != monster && obj != shared_from_this()) {
                    conti = false;
                }
            }
            for (const auto& monster : m_Monsters) {
                if (monster == shared_from_this()) {
                    continue;
                }
                if (Calculation::Equal(Calculation::AddPosition(this->GetPosition(), Calculation::MulPosition(randomDisplacement, 28)), monster->GetGoalPosition())) {
                    conti = false;
                }
            }

            if (conti) {
                grids = 0;
                pos = this->GetPosition();
                goalpos = Calculation::AddPosition(pos, Calculation::MulPosition(randomDisplacement, 28));
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
        
        if (this->IsCollision(m_Player, randomDisplacement) && static_cast<int>(glm::distance(pos, goalpos)) == 28) {
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
        if (Calculation::Equal(pos, goalpos)) {
            this->state = State::Stop;
            this->SetGoalPosition(this->GetPosition());
        }
    }
}