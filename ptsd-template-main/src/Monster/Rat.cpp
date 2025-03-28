#include "Monster/Rat.hpp"
#include <random>
#include "Player.hpp"
#include "Calculation.hpp"

Rat::Rat() : Monster(RESOURCE_DIR"/Monster/Rat.png", 4, 0, glm::vec2{1, 4}, 0, 105, 5, std::vector<int>{-50, 0, 0, 0, 0}, 1, 6, 2.0) {}

bool Rat::IsCollision(const std::shared_ptr<Character> &other, glm::vec2 displacement) {
    glm::vec2 thisSize = this->GetScaledSize();
    glm::vec2 otherSize = other->GetScaledSize();

    glm::vec2 thisPos = this->GetPosition() + displacement - glm::vec2({thisSize.x / 2.0, thisSize.y / 2.0});
    glm::vec2 otherPos = other->GetPosition() - glm::vec2({otherSize.x / 2.0, otherSize.y / 2.0});

    bool xOverlap = thisPos.x + thisSize.x > otherPos.x && otherPos.x + otherSize.x > thisPos.x;
    bool yOverlap = thisPos.y + thisSize.y > otherPos.y && otherPos.y + otherSize.y > thisPos.y;

    return xOverlap && yOverlap && this->GetVisibility();
}

void Rat::Move(glm::vec2 displacement, glm::vec2 goal) {
    if (((goal[0] - this->GetPosition().x) * displacement[0] + (goal[1] - this->GetPosition().y) * displacement[1]) > 0) {
        this->SetPosition(this->GetPosition() + displacement);
    }
    else {
        SetState(State::Stop);
    }
}

int Rat::Attack() {
    // 變成攻擊狀態
    return 0;
    SetState(State::Move);
}

void Rat::Update(std::vector<std::shared_ptr<ICollidable>> AllCollidableObjects, std::shared_ptr<Player> &m_Player) {
    // 定義四個位移方向，使用 glm::vec2
    glm::vec2 displacements[4] = {
        glm::vec2(0, 1), glm::vec2(0, -1), glm::vec2(1, 0), glm::vec2(-1, 0)
    };
    // 初始化隨機數生成器
    std::random_device rd;                   // 真實隨機數生成器
    std::mt19937 engine(rd());               // Mersenne Twister 引擎
    std::uniform_int_distribution<int> distIndex(0, 3);  // 生成 0~3 之間的隨機索引
    std::uniform_int_distribution<int> distValue(0, 4); // 生成 1~11 之間的隨機步長
    std::uniform_int_distribution<int> walkRate(1, 200); // 移動機率
    if (GetState() == State::Stop && walkRate(engine) == 1) {
        // 隨機選擇一個 displacement
        randomDisplacement = displacements[distIndex(engine)];
        pos = GetPosition();
        value = static_cast<float>(distValue(engine)) * 28.0f;
        SetState(State::Move);
    }
    if (GetState() == State::Move) {
        for (const auto& obj : AllCollidableObjects) {
            if (obj->IsCollision(shared_from_this(), -randomDisplacement) && obj != shared_from_this()) {
                SetState(State::Stop);
                return;
            }
        }
        // 往旁邊走攻擊距離看有沒有碰到玩家
        const std::vector<glm::vec2> directions = {
            {0, 1}, {0, -1}, {-1, 0}, {1, 0}
        };
        
        for (const auto& dir : directions) {
            if (this->IsCollision(m_Player, dir * m_TrackRange)) {
                m_Player->TakeDamage(Calculation::CalcuAttack(m_Attack, 0));
                return;
            }
        }
        
        Move(randomDisplacement, pos + randomDisplacement * value);
    }
    if (GetState() == State::Attack) {
        Attack();
    }
}