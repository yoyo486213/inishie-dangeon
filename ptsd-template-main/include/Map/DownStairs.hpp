#ifndef DOWNSTAIRS_HPP
#define DOWNSTAIRS_HPP

#include "pch.hpp"
#include "Character.hpp"
#include "ICollidable.hpp"
#include "Button.hpp"

namespace Util {
    class Renderer;
}

class DownStairs : public ICollidable, public Character {
public:
    DownStairs(const std::string& ImagePath, Util::Renderer *m_Root);
    
    bool IsCollision(const std::shared_ptr<Character> &other, glm::vec2 displacement) override;

    void OnCollision() override;

    void OffCollision() override;

    bool IfFouse() { return m_TextButton->IfFocus(); }

    bool IfClick() { return m_TextButton->IfClick(); }

    void ChangeImage(int index) { m_TextButton->ChangeImage(index); }
private:
    std::shared_ptr<Button> m_TextButton;
};

#endif //DOWNSTAIRS_HPP