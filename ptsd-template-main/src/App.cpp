#include "App.hpp"

#include "Util/Image.hpp"
#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include "Util/Logger.hpp"

#include "Character.hpp"
#include "AnimatedCharacter.hpp"

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
    m_SSdoor->SetPivot({0, 0});
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
    m_SSslidedown->SetPivot({0, 0});
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
    m_SSmenu->SetPivot({0, 0});
    m_Root.AddChild(m_SSmenu);

    m_NewGameBtn = std::make_shared<Character>("../Resources/Button/NewGame-1.bmp");
    m_NewGameBtn->SetZIndex(6);
    m_NewGameBtn->SetVisible(true);
    m_NewGameBtn->SetPosition({0, 0});
    m_Root.AddChild(m_NewGameBtn);


    m_CurrentState = State::UPDATE;
}

void App::Update() {
    
    //TODO: do your things here and delete this line <3
    m_SSdoor->Play();
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
