#ifndef UPSTAIRS_HPP
#define UPSTAIRS_HPP

#include "pch.hpp"
#include "ICollidable.hpp"
#include "Character.hpp"
#include "Button.hpp"

namespace Util {
    class Renderer;
}

class MyBGM;

class UpStairs : public ICollidable, public Character {
public:
    UpStairs(const std::string& ImagePath, Util::Renderer *m_Root);
    
    bool IsCollision(const std::shared_ptr<Character> &other, glm::vec2 displacement) override;

    void OnCollision() override;

    void OffCollision() override;

    bool IfFouse() { return m_TextButton->IfFocus(); }

    bool IfClick() { return m_TextButton->IfClick(); }

    void ChangeImage(int index) { m_TextButton->ChangeImage(index); }
private:
    std::shared_ptr<Button> m_TextButton;
};

#endif //UPSTAIRS_HPP