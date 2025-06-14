#include "Monster/Bat.hpp"
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

Bat::Bat() : Monster({RESOURCE_DIR"/Monster/Bat/Bat-0.png",
                      RESOURCE_DIR"/Monster/Bat/Bat-1.png",
                      RESOURCE_DIR"/Monster/Bat/Bat-2.png"}, 
                      8, 0, glm::vec2{2, 5}, 0, 125, 25, std::vector<int>{0, 0, 0, 0, 0}, 2, 12, 28.0) {
}

void Bat::Move(glm::vec2 displacement, glm::vec2 goal, std::vector<std::shared_ptr<Monster>> m_Monsters) {
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

        if (m_ImageIndex == 1) { 
            this->ChangeImage(2);
            this->m_ImageIndex = 2;
        }
        else if (m_ImageIndex == 2) {
            this->ChangeImage(1);
            this->m_ImageIndex = 1;
        }
        else {
            this->ChangeImage(1);
            this->m_ImageIndex = 1;
        }
    }
}

void Bat::Update(std::shared_ptr<Player> &m_Player, std::vector<std::shared_ptr<Character>> AllObjects, std::vector<std::shared_ptr<ICollidable>> AllCollidableObjects, std::vector<std::shared_ptr<InvisibleWall>> m_Invisiblewalls, std::vector<std::shared_ptr<Monster>> m_Monsters) {
    // 初始化隨機數生成器
    std::random_device rd;                   // 真實隨機數生成器
    std::mt19937 engine(rd());               // Mersenne Twister 引擎
    this->SetChangeImageCD(this->GetChangeImageCD() - Util::Time::GetDeltaTimeMs() / 1000.0f);
    this->SetAttackCD(this->GetAttackCD() - Util::Time::GetDeltaTimeMs() / 1000.0f);
    if (this->GetHP() > 0 && m_Player->GetHP() > 0 && (this->state == State::Stop || static_cast<int>(glm::distance(pos, goalpos)) == 28)) {
        // 往旁邊走攻擊距離看有沒有碰到玩家
        const std::vector<glm::vec2> directions = {
            {0, 1}, {0, -1}, {-1, 0}, {1, 0}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}
        };
        for (const auto& dir : directions) {
            if (this->IsCollision(m_Player, dir * m_TrackRange)) {
                if (this->GetAttackCD() <= 0) {
                    std::uniform_real_distribution<double> hitrate(0, 100.0);
                    int rate = hitrate(engine);
                    if (rate < m_Player->GetBlockrate()) {
                        std::cout << "Block!" << std::endl;
                        m_Player->PlayBlockSFX();
                        break;
                    }
                    if (rate > m_Hitrate / ((m_Player->GetDodgerate() + 100) / 100.0)) {
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
                    auto destructibleobject = std::dynamic_pointer_cast<DestructibleObject>(obj);
                    auto chest = std::dynamic_pointer_cast<Chest>(obj);
                    auto monster = std::dynamic_pointer_cast<Monster>(obj);
                    if (obj->IsCollision(shared_from_this(), Calculation::MulPosition(-dir, 14)) && obj != monster && obj != chest && obj != destructibleobject && obj != shared_from_this()) {
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

        if (this->state == State::Stop) {
            this->SetGoalPosition(this->GetPosition());
        }
    }
    if (this->state == State::Move) {
        for (const auto& obj : AllCollidableObjects) {
            auto destructibleobject = std::dynamic_pointer_cast<DestructibleObject>(obj);
            auto chest = std::dynamic_pointer_cast<Chest>(obj);
            auto monster = std::dynamic_pointer_cast<Monster>(obj);
            if (obj->IsCollision(shared_from_this(), -randomDisplacement) && obj != chest && obj != monster && obj != destructibleobject && obj != shared_from_this()) {
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

        Move(Calculation::MulPosition(randomDisplacement, 2), goalpos, m_Monsters);
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