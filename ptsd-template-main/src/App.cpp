#include "App.hpp"

#include "Util/Image.hpp"
#include "Util/Animation.hpp"
#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include "Util/Logger.hpp"

#include "MyBGM.hpp"
#include "Character.hpp"
#include "AnimatedCharacter.hpp"
#include "Menu.hpp"
#include "Button.hpp"
#include "MoveAnimated.hpp"

void App::Start() {
    LOG_TRACE("Start");

    // 開門畫面
    std::vector<std::string> StartAnimeImages; 
    StartAnimeImages.reserve(63);
    char buffer[100];
    for (int i = 0; i < 63; i++) {
        snprintf(buffer, sizeof(buffer), "../Resources/LoadingAnime/LoadingAnime-%02d.bmp", i);
        StartAnimeImages.emplace_back(buffer);
    }
    m_StartAnime = std::make_shared<AnimatedCharacter>(StartAnimeImages);
    m_StartAnime->SetZIndex(5);
    m_StartAnime->SetVisible(true);
    m_StartAnime->Play();
    m_Root.AddChild(m_StartAnime);

    // 建構開始畫面
    m_StartMenu = std::make_shared<StartMenu>(&m_Root);
    m_NewGameButton = std::make_shared<NewGameButton>(&m_Root);
    m_CreateCharacterMenu = std::make_shared<CreateCharacterMenu>(&m_Root);
    
    m_CurrentState = State::UPDATE;
}

void App::Update() {
    //TODO: do your things here and delete this line <3
    
    if (m_StartAnime->IfAnimationEnds()) {
        m_StartAnime->SetVisible(false);
        m_StartMenu->OpenMenu();
    }

    m_StartMenu->Update();
    if (m_StartMenu->SkipButton()) {
        m_NewGameButton->Skip();
    }
    if (m_StartMenu->OpenButton()) {
        m_NewGameButton->Open();
    }

    m_NewGameButton->Update();
    if (m_NewGameButton->IfClick()) {
        m_CreateCharacterMenu->OpenMenu();
    }
    
    if(m_CreateCharacterMenu->GetState() != Menu::State::Close) {
        m_CreateCharacterMenu->Update();
    }
    if (m_CreateCharacterMenu->GetState() != Menu::State::Open) {
        m_CreateCharacterMenu->Update();
    }
    if (m_CreateCharacterMenu->GetState() == Menu::State::Close) {
        m_NewGameButton->Skip();
    }

    m_Root.Update();
    /*
     * Do not touch the code below as they serve the purpose for
     * closing the window.
     */
    if (Util::Input::IsKeyUp(Util::Keycode::ESCAPE) ||
        Util::Input::IfExit()) {
        m_CurrentState = State::END;
    }
}

void App::End() { // NOLINT(this method will mutate members in the future)
    LOG_TRACE("End");
}
