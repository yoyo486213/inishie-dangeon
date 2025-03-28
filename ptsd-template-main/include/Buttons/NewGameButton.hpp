#ifndef NEWGAMEBUTTON_HPP
#define NEWGAMEBUTTON_HPP

#include "pch.hpp"

#include "Util/GameObject.hpp"
#include "Button.hpp"
namespace Util {
    class Renderer;
}
class Menu;

class NewGameButton : public Util::GameObject {
public:
    NewGameButton(Util::Renderer *m_Root);
    
    virtual ~NewGameButton() = default;

    void Open();
    void Skip();

    void Close();
    
    void Update();
    
    bool IfFocus() { return m_NewGameBtn->IfFocus(); }

    bool IfClick() { return m_NewGameBtn->IfClick(); }

    bool IfPressed() { return m_NewGameBtn->IfPressed(); }
private:
    std::shared_ptr<Button> m_NewGameBtn;
    std::shared_ptr<Menu> m_NewGameText;
};

#endif //NEWGAMEBUTTON_HPP