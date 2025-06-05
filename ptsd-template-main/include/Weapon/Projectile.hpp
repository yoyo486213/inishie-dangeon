#ifndef PROJECTILE_HPP
#define PROJECTILE_HPP

#include "pch.hpp"
#include "Util/Time.hpp"
#include "Character.hpp"
#include "ICollidable.hpp"
#include <iostream>

enum class State { 
    Flying, 
    Staying, 
    Ended 
};

enum class ProjectileBehaviorType {
    Default,
    AxeSpin,
    HealingCircle,
    OrbitingBoomerang
};

class Projectile : public ICollidable, public Character {
public:
    Projectile(std::string baseImagePath, glm::vec2 pos, float speed,
               glm::vec2 damage, int flightDistance,
               int skillRange = 0, float stayDuration = 0.0f, glm::vec2 startPos = {0.0f, 0.0f},
               ProjectileBehaviorType behaviorType = ProjectileBehaviorType::Default, bool collide = true,
               bool disappear = true)
        : Character(baseImagePath),
          m_Speed(speed),
          m_Damage(damage),
          m_MaxDistance(flightDistance * 28.0f),
          m_SkillRange(skillRange),
          m_StayDuration(stayDuration),
          m_Position(startPos),
          m_Start({0.0f, 0.0f}),
          m_BehaviorType(behaviorType),
          m_Collide(collide),
          m_Disappear(disappear)
    {
        m_Direction = glm::normalize(pos);
        m_Transform.rotation = atan2(m_Direction.y, m_Direction.x);
        this->SetPosition(m_Position);
        this->SetVisible(true);
        this->SetZIndex(60);
    }

    void Update() {
        switch (m_State) {
            case State::Flying:
                m_Position += m_Direction * m_Speed;
                this->SetPosition(m_Position);

                // 針對飛出去的斧頭旋轉
                if (m_BehaviorType == ProjectileBehaviorType::AxeSpin) {
                    m_Transform.rotation += 0.3f;
                }

                if (glm::length(m_Position - m_Start) >= m_MaxDistance) {
                    if (m_StayDuration > 0.0f) {
                        m_State = State::Staying;
                        OnEnterStay();  // 初始化特效
                    } else {
                        m_State = State::Ended;
                        this->SetVisible(false);
                    }
                }
                break;
            case State::Staying:
                m_StayDuration -= Util::Time::GetDeltaTimeMs() / 1000.f;
                StaySkill();  // 根據 m_BehaviorType 執行不同特效

                if (m_StayDuration <= 0) {
                    m_State = State::Ended;
                    this->SetVisible(false);
                }
                break;
            case State::Ended:
                break;
        }
    }

    void StaySkill() {
        switch (m_BehaviorType) {
            case ProjectileBehaviorType::AxeSpin:
                m_Transform.rotation += 0.3f;
                break;
            case ProjectileBehaviorType::HealingCircle:
                m_Transform.rotation += 0.1f;
                break;
            case ProjectileBehaviorType::OrbitingBoomerang:
                std::cout << "TEst" <<std::endl;
                break;
            case ProjectileBehaviorType::Default:
            default:
                // 無特殊停留技能
                break;
        }
    }

    void OnEnterStay() {
        // 若需要可初始化粒子特效、音效播放等
    }

    int GetSkillRange() const { return m_SkillRange; }
    glm::vec2 GetDamage() const { return m_Damage; }
    glm::vec2 GetPosition() const { return m_Position; }
    bool CanCollide() const { return m_Collide; }
    bool ShouldDisappear() const { return m_Disappear; }

    void SetSpeed(float speed) { m_Speed = speed; }
    void SetState(State state) { m_State = state; }

    bool IsCollision(const std::shared_ptr<Character> &other, glm::vec2 displacement) override {
        glm::vec2 thisSize = this->GetScaledSize();
        glm::vec2 otherSize = other->GetScaledSize();

        glm::vec2 thisPos = this->GetPosition() + displacement - glm::vec2(thisSize.x / 2.0f, thisSize.y / 2.0f);
        glm::vec2 otherPos = other->GetPosition() - glm::vec2(otherSize.x / 2.0f, otherSize.y / 2.0f);

        bool xOverlap = thisPos.x + thisSize.x > otherPos.x && otherPos.x + otherSize.x > thisPos.x;
        bool yOverlap = thisPos.y + thisSize.y > otherPos.y && otherPos.y + otherSize.y > thisPos.y;

        return xOverlap && yOverlap && this->GetVisibility() && other->GetVisibility();
    }

    void OnCollision() override {}
    void OffCollision() override {}
private:
    State m_State = State::Flying;

    float m_Speed;
    glm::vec2 m_Damage;
    float m_MaxDistance;
    int m_SkillRange;
    float m_StayDuration;
    glm::vec2 m_Position;
    glm::vec2 m_Start;
    glm::vec2 m_Direction;
    ProjectileBehaviorType m_BehaviorType;
    bool m_Collide;
    bool m_Disappear;
};


#endif // PROJECTILE_HPP