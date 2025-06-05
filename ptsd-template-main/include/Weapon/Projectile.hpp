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
    FreeOrbiting
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
                if (glm::length(m_Position - m_Start) >= m_MaxDistance) {
                    if (m_StayDuration > 0.0f) {
                        m_State = State::Staying;
                        OnEnterStay();  // 初始化特效
                    } else {
                        m_State = State::Ended;
                        this->SetVisible(false);
                    }
                }

                m_Position += m_Direction * m_Speed;
                this->SetPosition(m_Position);

                // 針對飛出去的斧頭旋轉
                if (m_BehaviorType == ProjectileBehaviorType::AxeSpin) {
                    m_Transform.rotation += 0.3f;
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
            case ProjectileBehaviorType::FreeOrbiting: {
                float targetAngle = atan2(sin(m_OrbitAngle), cos(m_OrbitAngle));
                float currentAngle = glm::radians(m_Transform.rotation);

                // 用插值慢慢旋轉（0.001 旋轉跟隨速度）
                float smoothAngle = currentAngle + (targetAngle - currentAngle) * 0.001f;

                m_Transform.rotation = glm::degrees(smoothAngle);


                float deltaTime = Util::Time::GetDeltaTimeMs() / 1000.f;
                float timeSec = Util::Time::GetElapsedTimeMs() / 1000.f;

                // 忽近忽遠的半徑
                float dynamicRadius = m_OrbitBaseRadius + sin(timeSec * 2.0f + m_OrbitPhaseOffset) * m_OrbitRadiusRange;

                // 讓線速度保持穩定 => ω = v / r
                float targetLinearSpeed = 300.0f; // 每秒在圓上移動的長度（單位長度/秒）
                float angularSpeed = (dynamicRadius > 1e-3f) ? targetLinearSpeed / dynamicRadius : 0.0f;

                m_OrbitAngle += angularSpeed * deltaTime;

                glm::vec2 offset = glm::vec2(cos(m_OrbitAngle), sin(m_OrbitAngle)) * dynamicRadius;
                m_Position = m_OrbitCenter + offset;

                this->SetPosition(m_Position);
                break;
            }
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

    void SetOrbitAngle(float angle) { m_OrbitAngle = angle; }
    void SetOrbitPhaseOffset(float offset) { m_OrbitPhaseOffset = offset; }

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
    
    // 針對繞圈技能的額外參數
    float m_OrbitBaseRadius = 48.0f;      // 中心基準距離
    float m_OrbitRadiusRange = 8.0f;     // 最大忽遠忽近變化範圍（±28）
    float m_OrbitAngle = 0.0f;            // 當前角度
    float m_OrbitPhaseOffset = 0.0f;      // 每顆飛鏢角度偏移（避免三顆一起變）
    glm::vec2 m_OrbitCenter = {0.0f, 0.0f};  // 中心位置
};


#endif // PROJECTILE_HPP