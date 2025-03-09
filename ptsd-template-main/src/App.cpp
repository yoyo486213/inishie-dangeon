#include "App.hpp"

#include "Util/Image.hpp"
#include "Util/Animation.hpp"
#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include "Util/Logger.hpp"

#include "MyBGM.hpp"
#include "Character.hpp"
#include "AnimatedCharacter.hpp"
#include "MoveCharacter.hpp"
#include "MoveAnimated.hpp"

void App::Start() {
    LOG_TRACE("Start");

    std::vector<std::string> SSdoorImages; //SS=StartScreen
    SSdoorImages.reserve(63);
    char buffer[100];
    for (int i = 0; i < 63; i++) {
        snprintf(buffer, sizeof(buffer), "../Resources/LoadingAnime/LoadingAnime-%02d.bmp", i);
        SSdoorImages.emplace_back(buffer);
    }
    m_SSdoor = std::make_shared<AnimatedCharacter>(SSdoorImages);
    m_SSdoor->SetZIndex(5);
    m_SSdoor->SetVisible(true);
    m_Root.AddChild(m_SSdoor);
    
    std::vector<std::string> SSslidedownImages;
    SSslidedownImages.reserve(402);
    for (int i = 0; i < 402; i++) {
        snprintf(buffer, sizeof(buffer), "../Resources/MenuAnime/Slidedown/Slidedown-%03d.bmp", i);
        SSslidedownImages.emplace_back(buffer);
    }
    m_SSslidedown = std::make_shared<AnimatedCharacter>(SSslidedownImages);
    m_SSslidedown->SetZIndex(5);
    m_SSslidedown->SetVisible(false);
    m_Root.AddChild(m_SSslidedown);

    std::vector<std::string> SSmenuImages;
    SSmenuImages.reserve(120);
    for (int i = 0; i < 120; i++) {
        snprintf(buffer, sizeof(buffer), "../Resources/MenuAnime/Looping/Looping-%03d.bmp", i);
        SSmenuImages.emplace_back(buffer);
    }
    m_SSmenu = std::make_shared<AnimatedCharacter>(SSmenuImages);
    m_SSmenu->SetZIndex(5);
    m_SSmenu->SetVisible(false);
    m_Root.AddChild(m_SSmenu);

    std::vector<std::string> NewGameBtnImages;
    NewGameBtnImages.reserve(3);
    for (int i = 1; i < 4; i++) {
        snprintf(buffer, sizeof(buffer), "../Resources/button/Menu/NewGame/NewGame-%d.png", i);
        NewGameBtnImages.emplace_back(buffer);
    }
    m_NewGameBtn = std::make_shared<MoveCharacter>(NewGameBtnImages);
    m_NewGameBtn->SetZIndex(6);
    m_NewGameBtn->SetPosition({0, -300});
    m_NewGameBtn->SetVisible(false);
    m_Root.AddChild(m_NewGameBtn);

    m_NewGameText = std::make_shared<MoveCharacter>("../Resources/Text/NewGameText/NewGameText.png");
    m_NewGameText->SetZIndex(6);
    m_NewGameText->SetPosition({0, -75});
    m_NewGameText->SetVisible(false);
    m_Root.AddChild(m_NewGameText);

    m_CreateCharacter = std::make_shared<MoveCharacter>("../Resources/Menu/CreateCharacter/CreateCharacter.png");
    m_CreateCharacter->SetZIndex(7);
    m_CreateCharacter->SetVisible(false);
    m_Root.AddChild(m_CreateCharacter);

    m_CreateCharacterBGM = std::make_shared<MyBGM>("../Resources/MenuCloseSnd.wav");

    std::vector<std::string> SkinDoorImages;
    SkinDoorImages.reserve(20);
    for (int i = 0; i < 20; i++) {
        snprintf(buffer, sizeof(buffer), "../Resources/SkinDoor-%02d.png", i);
        SkinDoorImages.emplace_back(buffer);
    }
    m_SkinDoor = std::make_shared<MoveAnimated>(SkinDoorImages);
    m_SkinDoor->SetZIndex(8);
    m_SkinDoor->SetVisible(false);
    m_Root.AddChild(m_SkinDoor);
    
    m_SSdoor->Play();
    m_CurrentState = State::UPDATE;
}

void App::Update() {
    
    //TODO: do your things here and delete this line <3
    
    if (m_SSdoor->IfAnimationEnds()) {
        m_SSdoor->SetVisible(false);
        m_SSslidedown->SetVisible(true);
        m_SSslidedown->Play();
    }
    if (m_SSslidedown->IfAnimationEnds()) {
        m_SSslidedown->SetVisible(false);
        m_SSmenu->SetVisible(true);
        m_SSmenu->Play();
        m_SSmenu->SetLooping(true);
    }
    else if (Util::Input::IsKeyUp(Util::Keycode::MOUSE_LB) && m_SSdoor->IfAnimationEnds()) { // can del
        m_SSslidedown->SetCurrentFrame(400);
        m_NewGameBtn->SetVisible(true);
        m_NewGameBtn->SetPosition({0, -155});
    }
    if (m_SSslidedown->IfAnimationToIndex(208)) {
        m_NewGameBtn->SetVisible(true);
        m_NewGameBtn->Play();
    }
    if (m_NewGameBtn->GetState()) {
        m_NewGameBtn->Move({0, 10}, {0, -155});
    }

    if (m_NewGameBtn->IfFocus()) {
        m_NewGameBtn->ChangeImage(2);
        m_NewGameText->SetVisible(true);
    }
    else { 
        m_NewGameBtn->ChangeImage(1); 
        m_NewGameText->SetVisible(false);
    }
    if (m_NewGameBtn->IfClick()) {
        m_NewGameBtn->ChangeImage(3);
        m_CreateCharacter->SetPosition({0, 300});
        m_CreateCharacter->SetVisible(true);
        m_CreateCharacter->Play();
        m_SkinDoor->SetPosition({-4, 414});
        m_SkinDoor->SetVisible(true);
        
        m_SkinDoor->SetCurrentFrame(8);

        m_CreateCharacterBGM->Play(0);
        
    }
    if (m_CreateCharacter->GetState()) {
        m_CreateCharacter->Move({0, -20}, {0, 0});
        m_SkinDoor->Move({0, -20}, {-4, 115});
    }
    // if (m_CreateCharacter->GetVisibility() && (m_SkinChooseLDoor->IfClick()) {
        
    // }

    m_Root.Update();
    /*
     * Do not touch the code below as they serve the purpose for
     * closing the window.
     */
    if (Util::Input::IsKeyUp(Util::Keycode::BACKSPACE)) {
        m_CreateCharacter->SetVisible(false);
    }
    if (Util::Input::IsKeyUp(Util::Keycode::ESCAPE) ||
        Util::Input::IfExit()) {
        m_CurrentState = State::END;
    }
}

void App::End() { // NOLINT(this method will mutate members in the future)
    LOG_TRACE("End");
}
