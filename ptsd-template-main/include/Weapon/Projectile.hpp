#ifndef PROJECTILE_HPP
#define PROJECTILE_HPP

#include "pch.hpp"
#include "Util/Input.hpp"
#include "Character.hpp"
#include "ICollidable.hpp"
#include <iostream>

class Projectile : public ICollidable, public Character {
public:
    enum class Direction {
        RIGHT = 0, RIGHT_DOWN, DOWN, LEFT_DOWN,
        LEFT, LEFT_UP, UP, RIGHT_UP
    };

    Projectile(std::string baseImagePath, float speed, glm::vec2 damage, int skillRange)
        : Character(GetDirectionalImage(baseImagePath, GetDirection(Util::Input::GetCursorPosition())))
        , m_Position({0.0f, 0.0f})
        , m_Start({0.0f, 0.0f})
        , m_Speed(speed)
        , m_Damage(damage)
        , m_MaxDistance(skillRange * 28.0f)
    {
        m_Direction = glm::normalize(Util::Input::GetCursorPosition());  // 算出單位方向向量
        this->SetVisible(true);
        this->SetZIndex(60);
    }

    void Update() {
        m_Position += m_Direction * m_Speed;
        this->SetPosition(m_Position);

        // 如果已飛超過最大距離，就消失
        if (glm::length(m_Position - m_Start) >= m_MaxDistance) {
            this->SetVisible(false);  // 或交給 Map 移除該投射物
        }
    }

    glm::vec2 GetDamage() const { return m_Damage; }
    glm::vec2 GetPosition() const { return m_Position; }

    bool IsCollision(const std::shared_ptr<Character> &other, glm::vec2 displacement) override {
        glm::vec2 thisSize = this->GetScaledSize();
        glm::vec2 otherSize = other->GetScaledSize();

        glm::vec2 thisPos = this->GetPosition() + displacement - glm::vec2(thisSize.x / 2.0f, thisSize.y / 2.0f);
        glm::vec2 otherPos = other->GetPosition() - glm::vec2(otherSize.x / 2.0f, otherSize.y / 2.0f);

        bool xOverlap = thisPos.x + thisSize.x > otherPos.x && otherPos.x + otherSize.x > thisPos.x;
        bool yOverlap = thisPos.y + thisSize.y > otherPos.y && otherPos.y + otherSize.y > thisPos.y;

        return xOverlap && yOverlap && this->GetVisibility();
    }

    void OnCollision() override {}
    void OffCollision() override {}
private:
    static Direction GetDirection(const glm::vec2& dir) {
        float angle = atan2(dir.y, dir.x) * 180.0f / 3.14159f;
        if (angle < 0) angle += 360.0f;
        int octant = static_cast<int>((angle + 22.5f) / 45.0f) % 8;
        return static_cast<Direction>(octant);
    }

    static std::string GetDirectionalImage(const std::string& basePath, Direction dir) {
        const char* angles[] = {"0", "45", "90", "135", "180", "225", "270", "315"};
        std::string path = basePath;
        size_t dot = path.find_last_of('.');
        if (dot != std::string::npos) {
            path.insert(dot, "_" + std::string(angles[static_cast<int>(dir)]));
        }
        return path;
    }

    glm::vec2 m_Position;
    glm::vec2 m_Start;
    glm::vec2 m_Direction;
    float m_Speed;
    glm::vec2 m_Damage;
    float m_MaxDistance;
};

#endif // PROJECTILE_HPP