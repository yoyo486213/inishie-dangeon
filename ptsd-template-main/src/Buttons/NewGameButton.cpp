#include "Buttons/NewGameButton.hpp"
#include <memory>

NewGameButton::NewGameButton(Util::Renderer *m_Root) {
    char buffer[100];
    //初始化按鈕
    std::vector<std::string> NewGameBtnImages;  
    NewGameBtnImages.reserve(3);
    for (int i = 1; i < 4; i++) {
        snprintf(buffer, sizeof(buffer), "../Resources/button/Menu/NewGame/NewGame-%d.png", i);
        NewGameBtnImages.emplace_back(buffer);
    }
    m_NewGameBtn = std::make_shared<Button>(NewGameBtnImages);
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

void NewGameButton::Open(){
    m_NewGameBtn->SetVisible(true);
    m_NewGameBtn->SetState(Button::State::Open);
}
void NewGameButton::Skip(){
    m_NewGameBtn->SetVisible(true);
    m_NewGameBtn->SetPosition({0, -155});
}

void NewGameButton::Update(){
    if (m_NewGameBtn->IfPressed()) { 
        m_NewGameBtn->ChangeImage(3); 
        m_NewGameText->SetVisible(false);
    }
    else if (m_NewGameBtn->IfClick()) {
        m_NewGameBtn->SetVisible(false);
    }
    else if (m_NewGameBtn->IfFocus()) {
        m_NewGameBtn->ChangeImage(2);
        m_NewGameText->SetVisible(true);
    }
    else {
        m_NewGameBtn->ChangeImage(1);
    }
    
    if (m_NewGameBtn->GetState() == Button::State::Open) {
        m_NewGameBtn->Move({0, 10}, {0, -155});
    }
}