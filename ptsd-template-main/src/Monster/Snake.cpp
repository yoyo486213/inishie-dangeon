#include "Monster/Snake.hpp"
#include "Util/Time.hpp"
#include <random>
#include "Map/InvisibleWall.hpp"
#include "Player.hpp"
#include "Calculation.hpp"
#include "Character.hpp"
#include <iostream>
#include <algorithm> // std::max
#include <cmath>    // std::pow

Snake::Snake() : Monster(RESOURCE_DIR"/Monster/Snake.png", 18, 0, glm::vec2{2, 5}, 0, 108, 8, std::vector<int>{0, -50, 0, 0, 0}, 1, 24, 28.0) {}

bool Snake::IsCollision(const std::shared_ptr<Character> &other, glm::vec2 displacement) {
    glm::vec2 thisSize = this->GetScaledSize();
    glm::vec2 otherSize = other->GetScaledSize();

    glm::vec2 thisPos = this->GetPosition() + displacement - glm::vec2({thisSize.x / 2.0, thisSize.y / 2.0});
    glm::vec2 otherPos = other->GetPosition() - glm::vec2({otherSize.x / 2.0, otherSize.y / 2.0});

    bool xOverlap = thisPos.x + thisSize.x > otherPos.x && otherPos.x + otherSize.x > thisPos.x;
    bool yOverlap = thisPos.y + thisSize.y > otherPos.y && otherPos.y + otherSize.y > thisPos.y;

    return xOverlap && yOverlap && this->GetVisibility();
}

void Snake::Move(glm::vec2 displacement, glm::vec2 goal) {
    if (((goal.x - pos.x) * displacement.x + (goal.y - pos.y) * displacement.y) > 0) {
        if ((pos.x < 0 && pos.x + displacement.x > 0) || (pos.x > 0 && pos.x + displacement.x < 0) || static_cast<int>(pos.x + displacement.x) == 0){
            throughzero = true;
            goalgrids += 1;
            this->trackdisplacement = Calculation::GetDirection(glm::round(-this->GetPosition()));
            this->trackpos = {0, this->GetPosition().y};
        }
        if ((pos.y < 0 && pos.y + displacement.y > 0) || (pos.y > 0 && pos.y + displacement.y < 0) || static_cast<int>(pos.y + displacement.y) == 0) {
            throughzero = true;
            goalgrids += 1;
            this->trackdisplacement = Calculation::GetDirection(glm::round(-this->GetPosition()));
            this->trackpos = {this->GetPosition().x, 0};
        }

        pos += displacement;
        this->SetPosition(Calculation::AddPosition(this->GetPosition(), displacement));
    }
    else {
        grids++;
        goalpos = Calculation::AddPosition(pos, Calculation::MulPosition(randomDisplacement, 28));
        if (grids >= goalgrids) {
            this->state = State::Stop;
        }
    }
}

void Snake::Update(std::shared_ptr<Player> &m_Player, std::vector<std::shared_ptr<Character>> AllObjects, std::vector<std::shared_ptr<ICollidable>> AllCollidableObjects, std::vector<std::shared_ptr<InvisibleWall>> m_Invisiblewalls, std::vector<std::shared_ptr<Monster>> m_Monsters) {
    // 初始化隨機數生成器
    std::random_device rd;                   // 真實隨機數生成器
    std::mt19937 engine(rd());               // Mersenne Twister 引擎
    std::uniform_int_distribution<int> distIndex(0, 3);  // 生成 0~3 之間的隨機索引
    std::uniform_int_distribution<int> distValue(1, 11); // 生成 1~11 之間的隨機步長
    std::uniform_int_distribution<int> walkRate(1, 30); // 移動機率
    this->SetAttackCD(this->GetAttackCD() - Util::Time::GetDeltaTimeMs() / 1000.0f);
    if (m_Player->GetHP() > 0 && (this->state == State::Stop || static_cast<int>(glm::distance(pos, goalpos)) == 28)) {
        // 往旁邊走攻擊距離看有沒有碰到玩家
        const std::vector<glm::vec2> directions = {
            {0, 1}, {0, -1}, {-1, 0}, {1, 0}
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
        this->goalchange = true;
        throughzero = false;

        if (static_cast<int>(this->GetPosition().x) == 0 || static_cast<int>(this->GetPosition().y) == 0) {
            bool conti = true;
            for (int dis=1; dis <= static_cast<int>(std::abs(glm::distance(this->GetPosition(), m_Player->GetPosition()))) / 28; dis++) {
                for (const auto& obj : AllCollidableObjects) {
                    if (obj->IsCollision(shared_from_this(), -this->trackdisplacement * static_cast<float>(dis) * 28.f) && obj != shared_from_this()) {
                        conti = false;
                    }
                }
            }
            if (conti) {
                this->goalchange = false;
                pos = this->GetPosition();
                randomDisplacement = Calculation::GetDirection(-this->GetPosition());
                goalpos = Calculation::AddPosition(pos, Calculation::MulPosition(randomDisplacement, 28));
                grids = 0;
                goalgrids = 11;
                this->state = State::Move;
            }
        }

        // 隨機選擇一個方向
        if (walkRate(engine) == 1 && this->state == State::Stop) {
            // 定義四個位移方向，使用 glm::vec2
            glm::vec2 displacements[4] = {
                glm::vec2(0, 1), glm::vec2(0, -1), glm::vec2(1, 0), glm::vec2(-1, 0)
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

        if (this->goalchange && throughzero && static_cast<int>(glm::distance(pos, goalpos)) == 28){
            throughzero = false;

            bool conti = true;
            for (int dis=1; dis <= static_cast<int>(std::abs(glm::distance(this->trackpos, m_Player->GetPosition()))) / 28; dis++) {
                for (const auto& obj : AllCollidableObjects) {
                    if (obj->IsCollision(shared_from_this(), -this->trackdisplacement * static_cast<float>(dis) * 28.f) && obj != shared_from_this()) {
                        conti = false;
                    }
                }
            }
            
            if (conti) {
                this->goalchange = false;
                pos = this->GetPosition();
                randomDisplacement = this->trackdisplacement;
                goalpos = Calculation::AddPosition(pos, Calculation::MulPosition(randomDisplacement, 28));
                grids = 0;
                goalgrids = 11;
            }
        }

        if (!this->goalchange) {
            bool uncollidable = true;
            if (!this->IsCollision(m_Player, randomDisplacement * static_cast<float>(std::min(4, static_cast<int>(std::pow(2, grids)))))) {
                for (const auto& obj : AllCollidableObjects) {
                    if (obj->IsCollision(shared_from_this(), -randomDisplacement * 2.f * static_cast<float>(std::min(4, static_cast<int>(std::pow(2, grids))))) && obj != shared_from_this()) {
                        uncollidable = false;
                    }
                }
            
                if (uncollidable) {
                    Move(randomDisplacement * static_cast<float>(std::min(4, static_cast<int>(std::pow(2, grids)))), goalpos);
                }
                else {
                    Move(randomDisplacement, goalpos);
                }
            }
            else if (!this->IsCollision(m_Player, randomDisplacement * static_cast<float>(std::min(2, static_cast<int>(std::pow(2, grids)))))) {
                uncollidable = true;
                for (const auto& obj : AllCollidableObjects) {
                    if (obj->IsCollision(shared_from_this(), -randomDisplacement * 2.f * static_cast<float>(std::min(2, static_cast<int>(std::pow(2, grids))))) && obj != shared_from_this()) {
                        uncollidable = false;
                    }
                }

                if (uncollidable) {  
                    Move(randomDisplacement * static_cast<float>(std::min(2, static_cast<int>(std::pow(2, grids)))), goalpos);
                }
                else {
                    Move(randomDisplacement, goalpos);
                }
            }
            else {
                Move(randomDisplacement, goalpos);
            }
        }
        else {
            Move(randomDisplacement, goalpos);
        }
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