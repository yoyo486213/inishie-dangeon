#ifndef PROJECTILE_HPP
#define PROJECTILE_HPP

#include "pch.hpp"
#include "Character.hpp"
#include "IMoveable.hpp"
#include "ICollidable.hpp"

class Projectile : public IMoveable, public ICollidable, public Character {
public:
    // 定義8個方向的枚舉
    enum class Direction {
        RIGHT = 0,      // 0度
        RIGHT_DOWN,     // 45度
        DOWN,          // 90度
        LEFT_DOWN,     // 135度
        LEFT,          // 180度
        LEFT_UP,       // 225度
        UP,            // 270度
        RIGHT_UP       // 315度
    };

    Projectile(std::string baseImagePath, glm::vec2 position, glm::vec2 direction, 
               float speed, int damage)
        : Character(GetDirectionalImage(baseImagePath, GetDirection(direction)))
        , m_Position(position)
        , m_Direction(direction)
        , m_Speed(speed)
        , m_Damage(damage)
        , m_IsActive(true) {}

    void Update() {
        if (!m_IsActive) return;
        
        m_Position += m_Direction * m_Speed;
        
        // 檢查碰撞
        CheckCollision();
    }

    int GetDamage() const { return m_Damage; }
    bool IsActive() const { return m_IsActive; }
    glm::vec2 GetPosition() const { return m_Position; }

    // 實現 ICollidable 介面
    void OnCollision() override {};

private:
    // 根據向量計算8方向之一
    static Direction GetDirection(const glm::vec2& dir) {
        float angle = atan2(dir.y, dir.x) * 180.0f / 3.14159f;
        if (angle < 0) angle += 360.0f;

        // 將360度分成8份，每份45度
        int octant = static_cast<int>((angle + 22.5f) / 45.0f) % 8;
        return static_cast<Direction>(octant);
    }

    // 根據方向獲取對應的圖片路徑
    static std::string GetDirectionalImage(const std::string& basePath, Direction dir) {
        // 假設圖片命名格式為：base_0.png, base_45.png 等
        const char* angles[] = {"0", "45", "90", "135", "180", "225", "270", "315"};
        std::string path = basePath;
        size_t dot = path.find_last_of('.');
        if (dot != std::string::npos) {
            path.insert(dot, "_" + std::string(angles[static_cast<int>(dir)]));
        }
        return path;
    }

    void CheckCollision(std::vector<std::shared_ptr<ICollidable>> AllCollidableObjects) {
        // 獲取場景中的所有可碰撞物體
        auto colliders = GetNearbyColliders(AllCollidableObjects);
        for (const auto& collider : colliders) {
            if (IsColliding(collider)) {
                OnCollision();
                break;
            }
        }
    }

    // 獲取附近的碰撞物體（需要實現）
    std::vector<std::shared_ptr<ICollidable>> GetNearbyColliders(std::vector<std::shared_ptr<ICollidable>> AllCollidableObjects) {
        // TODO: 實現獲取附近物體的邏輯
        return AllCollidableObjects;
    }

    // 檢查是否與其他物體碰撞（需要實現）
    bool IsColliding(std::shared_ptr<ICollidable> other) {
        if(other->)
        return false;
    }

    glm::vec2 m_Position;
    glm::vec2 m_Direction;
    float m_Speed;
    int m_Damage;
    bool m_IsActive;  // 用於標記投射物是否有效
};

#endif // PROJECTILE_HPP