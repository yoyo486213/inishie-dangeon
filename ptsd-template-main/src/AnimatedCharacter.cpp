#include "AnimatedCharacter.hpp"

AnimatedCharacter::AnimatedCharacter(const std::vector<std::string>& Imagepath) {
    m_Drawable = std::make_shared<Util::Animation>(Imagepath, false, 10, false, 0);
}

bool AnimatedCharacter::IfAnimationToIndex(int index) const {
    auto animation = std::dynamic_pointer_cast<Util::Animation>(m_Drawable);
        return animation->GetCurrentFrameIndex() == index;
}

bool AnimatedCharacter::IfAnimationEnds() const {
    auto animation = std::dynamic_pointer_cast<Util::Animation>(m_Drawable);
        return animation->GetCurrentFrameIndex() == animation->GetFrameCount() - 1;
}