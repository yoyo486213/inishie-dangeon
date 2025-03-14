#ifndef ANIMATEDCHARACTER_HPP
#define ANIMATEDCHARACTER_HPP

#include "pch.hpp"

#include "Util/Animation.hpp"
#include "Util/GameObject.hpp"

class AnimatedCharacter : public Util::GameObject {
public:
    explicit AnimatedCharacter(const std::vector<std::string>& Imagepath);

    void Play() { std::dynamic_pointer_cast<Util::Animation>(m_Drawable)->Play(); }

    void SetLooping(bool looping) { std::dynamic_pointer_cast<Util::Animation>(m_Drawable)->SetLooping(looping); }

    void SetCurrentFrame(std::size_t index) { std::dynamic_pointer_cast<Util::Animation>(m_Drawable)->SetCurrentFrame(index);}

    std::size_t GetCurrentFrameIndex() const { return std::dynamic_pointer_cast<Util::Animation>(m_Drawable)->GetCurrentFrameIndex(); }

    std::size_t GetFrameCount() const { return std::dynamic_pointer_cast<Util::Animation>(m_Drawable)->GetFrameCount(); }

    glm::vec2 GetPosition() { return {m_Transform.translation.x, m_Transform.translation.y}; }

    [[nodiscard]] bool GetVisibility() const { return m_Visible; }
    
    void SetPosition(const glm::vec2& Position) { m_Transform.translation = Position; }

    [[nodiscard]] bool IfAnimationToIndex(int index) const;

    [[nodiscard]] bool IfAnimationEnds() const;
    
    void End();
};

#endif
