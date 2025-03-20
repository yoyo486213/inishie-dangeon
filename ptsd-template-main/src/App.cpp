#include "App.hpp"

#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include "Util/Logger.hpp"

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
    m_NameKeyBoard = std::make_shared<NameKeyBoard>(&m_Root);
    
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
        // m_NewGameButton->Close();
        // m_CreateCharacterMenu->OpenMenu();
        m_NewGameButton->SetVisible(false);
        
        m_Butterfly = std::make_shared<Character>("../Resources/Character/Butterfly.png");
        m_Butterfly->SetZIndex(15);
        m_Butterfly->SetPosition({0, 0});
        m_Butterfly->SetVisible(true);
        m_Root.AddChild(m_Butterfly);
        
        m_map = std::make_shared<Map>(&m_Root);
        SetState(true);
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
    if (m_map) {
        m_map->Update();
        
        if (Util::Input::IsKeyPressed(Util::Keycode::W)) {
            m_map->Move({0, -2.5});
        }
        if (Util::Input::IsKeyPressed(Util::Keycode::A)) {
            m_map->Move({2.5, 0});
        }
        if (Util::Input::IsKeyPressed(Util::Keycode::S)) {
            m_map->Move({0, 2.5});
        }
        if (Util::Input::IsKeyPressed(Util::Keycode::D)) {
            m_map->Move({-2.5, 0});
        }
    }
    
    if (Util::Input::IsKeyUp(Util::Keycode::ESCAPE) ||
        Util::Input::IfExit()) {
        m_CurrentState = State::END;
    }
}

void App::End() { // NOLINT(this method will mutate members in the future)
    LOG_TRACE("End");
}
