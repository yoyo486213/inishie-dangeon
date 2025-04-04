#include "Menus/StartMenu.hpp"
#include "Util/Renderer.hpp"
#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include "AnimatedCharacter.hpp"

StartMenu::StartMenu(Util::Renderer *m_Root) {
    char buffer[200];

    //初始化下滑動畫
    std::vector<std::string> SSslidedownImages;
    SSslidedownImages.reserve(402);
    for (int i = 0; i < 402; i++) {
        snprintf(buffer, sizeof(buffer), RESOURCE_DIR"/MenuAnime/Slidedown/Slidedown-%03d.bmp", i);
        SSslidedownImages.emplace_back(buffer);
    }
    m_SSslidedown = std::make_shared<AnimatedCharacter>(SSslidedownImages);
    m_SSslidedown->SetZIndex(5);
    m_SSslidedown->SetVisible(false);
    m_SSslidedown->SetLooping(false);
    m_Root->AddChild(m_SSslidedown);

    //初始化循環動畫
    std::vector<std::string> SSmenuImages;
    SSmenuImages.reserve(120);
    for (int i = 0; i < 120; i++) {
        snprintf(buffer, sizeof(buffer), RESOURCE_DIR"/MenuAnime/Looping/Looping-%03d.bmp", i);
        SSmenuImages.emplace_back(buffer);
    }
    m_SSmenu = std::make_shared<AnimatedCharacter>(SSmenuImages);
    m_SSmenu->SetZIndex(5);
    m_SSmenu->SetVisible(false);
    m_Root->AddChild(m_SSmenu);
}

void StartMenu::OpenMenu() {
    MenuState = StartMenu::State::Open;
    m_SSslidedown->SetVisible(true);
    m_SSslidedown->Play();
}

bool StartMenu::OpenButton() {
    return m_SSslidedown->IfAnimationToIndex(208);
}
bool StartMenu::SkipButton() {
    return MenuState == StartMenu::State::Skip;
}

void StartMenu::Update() {
    if (m_SSslidedown->IfAnimationEnds()) {
        m_SSslidedown->SetVisible(false);
        m_SSmenu->SetVisible(true);
        m_SSmenu->Play();
        m_SSmenu->SetLooping(true);
    }
    else if (Util::Input::IsKeyUp(Util::Keycode::MOUSE_LB) && MenuState == StartMenu::State::Open) {
        MenuState = StartMenu::State::Skip;
        m_SSslidedown->SetCurrentFrame(400);
    }
}