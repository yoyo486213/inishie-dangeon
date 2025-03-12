#include "Menus/CreateCharacterMenu.hpp"

CreateCharacterMenu::CreateCharacterMenu() {
    m_CreateCharacterMenu = std::make_shared<Menu>("../Resources/Menu/CreateCharacter/CreateCharacter.png");
    m_CreateCharacterMenu->SetZIndex(7);
    m_CreateCharacterMenu->SetVisible(false);


    char buffer[100];
    std::vector<std::string> m_CreateCharacter_XImages;
    m_CreateCharacter_XImages.reserve(3);
    for (int i = 1; i < 4; i++) {
        snprintf(buffer, sizeof(buffer), "../Resources/Button/CreateCharacterCloseButton/CreateCharacterCloseButton-%d.bmp", i);
        m_CreateCharacter_XImages.emplace_back(buffer);
    }
    m_CreateCharacter_X = std::make_shared<Button>(m_CreateCharacter_XImages);
    m_CreateCharacter_X->SetZIndex(8);
    m_CreateCharacter_X->SetVisible(false);
    m_CreateCharacter_X->SetPosition({223, 184}); 


    std::vector<std::string> m_WarriorDoorImages;
    m_WarriorDoorImages.reserve(23);
    for (int i = 0; i < 23; i++) {
        snprintf(buffer, sizeof(buffer), "../Resources/MenuAnime/SkinDoor/SkinDoor-%02d.png", i);
        m_WarriorDoorImages.emplace_back(buffer);
    }
    m_WarriorDoor = std::make_shared<MoveAnimated>(m_WarriorDoorImages);
    m_WarriorDoor->SetZIndex(8);
    m_WarriorDoor->SetVisible(false);


    m_WarriorDoorFrame = std::make_shared<Menu>("../Resources/Menu/SkinDoorFrame/SkinDoorFrame.png");
    m_WarriorDoorFrame->SetZIndex(9);
    m_WarriorDoorFrame->SetVisible(false);
    m_WarriorDoorFrame->SetPosition({-3.5, 114.5});


    m_WarriorDoorText = std::make_shared<Menu>("../Resources/Text/SkinDoorText/SkinDoorText.png");
    m_WarriorDoorText->SetZIndex(9);
    m_WarriorDoorText->SetVisible(false);
    m_WarriorDoorText->SetPosition({-3.5, 10});
}