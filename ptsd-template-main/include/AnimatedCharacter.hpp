#ifndef AnimatedCharacter_HPP
#define AnimatedCharacter_HPP

#include "pch.hpp"

#include "Util/Animation.hpp"
#include "Util/GameObject.hpp"

class AnimatedCharacter : public Util::GameObject {
public:
    explicit AnimatedCharacter(const std::vector<std::string>& Imagepath);

    void Play() {
        std::dynamic_pointer_cast<Util::Animation>(m_Drawable)->Play();
    }

    void SetLooping(bool looping) {
        std::dynamic_pointer_cast<Util::Animation>(m_Drawable)->SetLooping(looping);
    }

    [[nodiscard]] bool IfAnimationEnds() const;
    
    void End();
};

#endif
