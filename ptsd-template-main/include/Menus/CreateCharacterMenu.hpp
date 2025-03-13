#ifndef CREATECHARACTERMENU_HPP
#define CREATECHARACTERMENU_HPP

#include "Util/Renderer.hpp"
#include "Util/Image.hpp"
#include "Util/Animation.hpp"
#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include "Util/Logger.hpp"

#include "../Menu.hpp"
#include "../Button.hpp"
#include "../MoveAnimated.hpp"
#include "../MyBGM.hpp"

class CreateCharacterMenu : public Util::GameObject{
public:
    CreateCharacterMenu(Util::Renderer *m_Root);

    void OpenMenu();

    void CloseMenu();

    void Update();

    Menu::State GetStats();

    virtual ~CreateCharacterMenu() = default;
private:
    std::shared_ptr<Menu> m_MenuBackGround;
    std::shared_ptr<Button> m_CreateCharacter_X;
    std::shared_ptr<MoveAnimated> m_WarriorDoor;
    std::shared_ptr<Menu> m_WarriorDoorFrame;
    std::shared_ptr<Menu> m_WarriorDoorText;
    std::shared_ptr<MyBGM> m_MenuOpenBGM;
    std::shared_ptr<MyBGM> m_MenuCloseBGM;
    std::shared_ptr<MyBGM> m_WarriorDoorBGM;
};

#endif //CREATECHARACTERMENU_HPP