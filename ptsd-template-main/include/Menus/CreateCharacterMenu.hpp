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

class CreateCharacterMenu : public Util::GameObject{
public:
    CreateCharacterMenu(Util::Renderer *m_Root);
    std::shared_ptr<Menu> m_CreateCharacterMenu;
    std::shared_ptr<Button> m_CreateCharacter_X;
    std::shared_ptr<MoveAnimated> m_WarriorDoor;
    std::shared_ptr<Menu> m_WarriorDoorFrame;
    std::shared_ptr<Menu> m_WarriorDoorText;
};

#endif //CREATECHARACTERMENU_HPP