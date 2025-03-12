#ifndef CREATECHARACTERMENU_HPP
#define CREATECHARACTERMENU_HPP

#include "../Menu.hpp"
#include "../Button.hpp"
#include "../MoveAnimated.hpp"

class CreateCharacterMenu {
public:
    CreateCharacterMenu();
    std::shared_ptr<Menu> m_CreateCharacterMenu;
    std::shared_ptr<Button> m_CreateCharacter_X;
    std::shared_ptr<MoveAnimated> m_WarriorDoor;
    std::shared_ptr<Menu> m_WarriorDoorFrame;
    std::shared_ptr<Menu> m_WarriorDoorText;
};

#endif //CREATECHARACTERMENU_HPP