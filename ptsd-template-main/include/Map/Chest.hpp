#ifndef CHEST_HPP
#define CHEST_HPP

#include "pch.hpp"
#include "Util/Renderer.hpp"
#include "Character.hpp"
#include "Collidable.hpp"
#include "AnimatedCharacter.hpp"
#include <random>
#include <memory>

class Chest : public Collidable, public Character{
public:
    enum class TrapType {
        Fire,
        Ice,
        Lightning,
        Explode,
        Charm,
        Poison,
        None
    };

    Chest(const std::string& ImagePath, Util::Renderer *m_Root);

    virtual ~Chest() = default;

    std::shared_ptr<AnimatedCharacter> GetTrapAnimation() { return m_TrapAnimation; }

    bool IsCollision(std::shared_ptr<Character> &other, glm::vec2 displacement) override;

    void OnCollision() override;

    void OffCollision() override;
private:
    bool opened = false;
    TrapType m_TrapType = TrapType::None;
    std::shared_ptr<Character> m_BoxProgressBox;
    std::shared_ptr<Character> m_TrapBox;
    std::shared_ptr<AnimatedCharacter> m_BoxProgress;
    std::shared_ptr<AnimatedCharacter> m_TrapAnimation;
};

#endif //CHEST_HPP