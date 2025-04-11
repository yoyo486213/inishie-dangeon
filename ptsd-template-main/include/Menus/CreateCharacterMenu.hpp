#ifndef CREATECHARACTERMENU_HPP
#define CREATECHARACTERMENU_HPP

#include "pch.hpp"
#include "Util/GameObject.hpp"
#include "Util/Renderer.hpp"
#include "Menu.hpp"

namespace Util {
    class Renderer;
}
class Button;
class MoveAnimated;
class MyBGM;
class NameKeyBoard;

class CreateCharacterMenu : public Util::GameObject{
public:
    enum class State {
        Open,
        Close,
        Enter
    };

    CreateCharacterMenu(Util::Renderer *m_Root);
    
    virtual ~CreateCharacterMenu() = default;

    void OpenMenu();

    void CloseMenu();

    bool IfEnter();
    void Enter();

    void Update();

    Menu::State GetState() { return m_MenuBackGround->GetState(); }
private:
    std::shared_ptr<Menu> m_MenuBackGround;
    std::shared_ptr<Button> m_CreateCharacter_X;
    std::shared_ptr<MoveAnimated> m_WarriorDoor;
    std::shared_ptr<Menu> m_WarriorDoorFrame;
    std::shared_ptr<Menu> m_WarriorDoorText;
    
    std::shared_ptr<MyBGM> m_MenuOpenBGM;
    std::shared_ptr<MyBGM> m_MenuCloseBGM;
    std::shared_ptr<MyBGM> m_WarriorDoorBGM;
    
    std::shared_ptr<NameKeyBoard> m_NameKeyBoard;

    State state;
};

#endif //CREATECHARACTERMENU_HPP