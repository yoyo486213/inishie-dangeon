#include "Buttons/NewGameButton.hpp"

NewGameButton::NewGameButton(Util::Renderer *m_Root) {
    char buffer[100];

    //初始化按鈕
    std::vector<std::string> NewGameBtnImages;  
    NewGameBtnImages.reserve(3);
    for (int i = 1; i < 4; i++) {
        snprintf(buffer, sizeof(buffer), "../Resources/button/Menu/NewGame/NewGame-%d.png", i);
        NewGameBtnImages.emplace_back(buffer);
    }
    m_NewGameBtn = std::make_shared<Menu>(NewGameBtnImages);
    m_NewGameBtn->SetZIndex(6);
    m_NewGameBtn->SetPosition({0, -300});
    m_NewGameBtn->SetVisible(false);
    m_Root->AddChild(m_NewGameBtn);

    //初始化文字
    m_NewGameText = std::make_shared<Menu>("../Resources/Text/NewGameText/NewGameText.png");
    m_NewGameText->SetZIndex(6);
    m_NewGameText->SetPosition({0, -75});
    m_NewGameText->SetVisible(false);
    m_Root->AddChild(m_NewGameText);

}


bool NewGameButton::GetClicked() { return m_NewGameBtn->IfClick(); }

Menu::State NewGameButton::GetStats(){
    return m_NewGameBtn->GetState();
}

void NewGameButton::Open(){
    m_NewGameBtn->SetVisible(true);
    m_NewGameBtn->SetState(Menu::State::Open);
}
void NewGameButton::Skip(){
    m_NewGameBtn->SetVisible(true);
    m_NewGameBtn->SetPosition({0, -155});
}

void NewGameButton::Update(){
    if (m_NewGameBtn->IfFocus()) {
        m_NewGameBtn->ChangeImage(2);
        m_NewGameText->SetVisible(true);
    }
    else { 
        m_NewGameBtn->ChangeImage(1); 
        m_NewGameText->SetVisible(false);
    }

    if (GetClicked()){
        m_NewGameBtn->ChangeImage(3);
        m_NewGameBtn->SetVisible(false);
    }

    if (m_NewGameBtn->GetState() == Menu::State::Open) {
        m_NewGameBtn->Move({0, 10}, {0, -155});
    }
}