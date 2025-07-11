#include "Menus/CreateCharacterMenu.hpp"
#include "Button.hpp"
#include "MoveAnimated.hpp"
#include "AnimatedCharacter.hpp"
#include "MyBGM.hpp"
#include "Buttons/NameKeyBoard.hpp"

CreateCharacterMenu::CreateCharacterMenu(Util::Renderer *m_Root) {
    //初始化創角菜單背景
    m_MenuBackGround = std::make_shared<Menu>(RESOURCE_DIR"/Menu/CreateCharacter/CreateCharacter.png");    
    m_MenuBackGround->SetZIndex(7);
    m_MenuBackGround->SetVisible(false);
    m_Root->AddChild(m_MenuBackGround);


    char buffer[200];
    //初始化創角菜單關閉按鈕
    std::vector<std::string> m_CreateCharacter_XImages; 
    m_CreateCharacter_XImages.reserve(3);
    for (int i = 1; i < 4; i++) {
        snprintf(buffer, sizeof(buffer), RESOURCE_DIR"/Button/CreateCharacterCloseButton/CreateCharacterCloseButton-%d.bmp", i);
        m_CreateCharacter_XImages.emplace_back(buffer);
    }
    m_CreateCharacter_X = std::make_shared<Button>(m_CreateCharacter_XImages);
    m_CreateCharacter_X->SetZIndex(8);
    m_CreateCharacter_X->SetVisible(false);
    m_CreateCharacter_X->SetPosition({223, 184}); 
    m_Root->AddChild(m_CreateCharacter_X);

    //初始化戰士門動畫
    std::vector<std::string> m_WarriorDoorImages;   
    m_WarriorDoorImages.reserve(23);
    for (int i = 0; i < 23; i++) {
        snprintf(buffer, sizeof(buffer), RESOURCE_DIR"/MenuAnime/SkinDoor/SkinDoor-%02d.png", i);
        m_WarriorDoorImages.emplace_back(buffer);
    }
    m_WarriorDoor = std::make_shared<MoveAnimated>(m_WarriorDoorImages);
    m_WarriorDoor->SetZIndex(9);
    m_WarriorDoor->SetVisible(false);
    m_Root->AddChild(m_WarriorDoor);

    //初始化戰士門邊框
    m_WarriorDoorFrame = std::make_shared<Menu>(RESOURCE_DIR"/Menu/SkinDoorFrame/SkinDoorFrame.png");   
    m_WarriorDoorFrame->SetZIndex(9);
    m_WarriorDoorFrame->SetVisible(false);
    m_WarriorDoorFrame->SetPosition({-3.5, 114.5});
    m_Root->AddChild(m_WarriorDoorFrame);

    //初始化戰士門文字框
    m_WarriorDoorText = std::make_shared<Menu>(RESOURCE_DIR"/Text/SkinDoorText/SkinDoorText.png");  
    m_WarriorDoorText->SetZIndex(9);
    m_WarriorDoorText->SetVisible(false);
    m_WarriorDoorText->SetPosition({-3.5, 10});
    m_Root->AddChild(m_WarriorDoorText);

    //初始化戰士角色
    m_WarriorCharacter = std::make_shared<Menu>(RESOURCE_DIR"/Player/Player-F-0.png");
    m_WarriorCharacter->SetZIndex(8);
    m_WarriorCharacter->SetVisible(false);
    m_WarriorCharacter->SetPosition({-3.5, 114.5});
    m_Root->AddChild(m_WarriorCharacter);

    //初始化BGM
    m_MenuOpenBGM = std::make_shared<MyBGM>(RESOURCE_DIR"/BGM/MenuOpenSnd.wav");     
    m_MenuCloseBGM = std::make_shared<MyBGM>(RESOURCE_DIR"/BGM/MenuCloseSnd.wav");
    m_WarriorDoorBGM = std::make_shared<MyBGM>(RESOURCE_DIR"/BGM/SkinDoorSnd.wav");

    m_NameKeyBoard = std::make_shared<NameKeyBoard>(m_Root);
}

void CreateCharacterMenu::OpenMenu(){
    state = State::Open;
    m_MenuBackGround->SetPosition({0, 500});
    m_MenuBackGround->SetVisible(true);
    m_MenuBackGround->SetState(Menu::State::Open);
    m_WarriorCharacter->SetPosition({-3.5, 614});
    m_WarriorCharacter->SetVisible(true);
    m_WarriorDoor->SetPosition({-3.5, 614});
    m_WarriorDoor->SetVisible(true);
    m_WarriorDoor->SetCurrentFrame(11); //先切到關門
    m_CreateCharacter_X->SetPosition({223, 684});
    m_CreateCharacter_X->SetVisible(true);
    m_CreateCharacter_X->ChangeImage(1);
    m_MenuOpenBGM->Play(0);
    m_NameKeyBoard->Open();
}

void CreateCharacterMenu::CloseMenu(){
    state = State::Close;
    m_CreateCharacter_X->ChangeImage(3);
    m_WarriorDoorFrame->SetUsed(false);
    m_MenuBackGround->SetState(Menu::State::Close);
    m_CreateCharacter_X->SetVisible(false);
    m_MenuCloseBGM->Play(0);
    m_NameKeyBoard->Closing();
    m_NameKeyBoard->DisableEnter();
}

void CreateCharacterMenu::Enter() {
    state = State::Close;
    m_NameKeyBoard->Close();
    m_NameKeyBoard->Closing();
    m_WarriorDoorFrame->SetUsed(false);
    m_MenuBackGround->SetState(Menu::State::Close);
    m_CreateCharacter_X->SetVisible(false);
}

bool CreateCharacterMenu::IfEnter() {
    return (m_NameKeyBoard->ClickContorlBtn() == 2);
}

void CreateCharacterMenu::Update(){
    m_NameKeyBoard->Update();
    int Contorl = m_NameKeyBoard->ClickContorlBtn();
    switch (Contorl)
    {
    case 3:
        CloseMenu();
        break;
    default:
        break;
    }
    

    if (m_MenuBackGround->GetState() == Menu::State::Open) {
        m_MenuBackGround->Move({0, -20}, {0, 0});
        m_WarriorDoor->Move({0, -20}, {-3.5, 115.5});
        m_WarriorCharacter->Move({0, -20}, {-3.5, 115.5});
        m_CreateCharacter_X->Move({0, -20}, {223, 184});
    }
    if (m_MenuBackGround->GetState() == Menu::State::Close) {
        m_MenuBackGround->Move({0, 20}, {0, 500});
        m_WarriorDoor->Move({0, 20}, {0, 500});
        m_WarriorCharacter->Move({0, 20}, {0, 500});
        m_CreateCharacter_X->Move({0, 20}, {0, 500});
    }

    if (m_CreateCharacter_X->IfFocus()) {
        m_CreateCharacter_X->ChangeImage(2);
    }

    if (m_CreateCharacter_X->IfPressed()) {
        m_CreateCharacter_X->ChangeImage(3);
    }

    if (m_CreateCharacter_X->IfClick()) {
        CloseMenu();
    }

    if (m_WarriorDoor->IfFocus() && !m_WarriorDoorFrame->GetUsed()) {
        m_WarriorDoorFrame->SetVisible(true);
        m_WarriorDoorText->SetVisible(true);
    }
    else {
        m_WarriorDoorFrame->SetVisible(false);
        m_WarriorDoorText->SetVisible(false);
    }

    if (m_MenuBackGround->GetVisibility() && m_WarriorDoor->IfClick()) {
        if (!m_WarriorDoor->IfAnimationEnds() && m_WarriorDoor->GetCurrentFrameIndex() >= m_WarriorDoor->GetFrameCount() / 2) {
            m_WarriorDoor->SetCurrentFrame(m_WarriorDoor->GetFrameCount() - m_WarriorDoor->GetCurrentFrameIndex());
        }
        std::dynamic_pointer_cast<AnimatedCharacter>(m_WarriorDoor)->Play();
        m_WarriorDoorBGM->Play(0);
        m_WarriorDoorFrame->SetUsed(true);
        m_WarriorDoorText->SetUsed(true);
        m_NameKeyBoard->EnableEnter();
    }
    
    if (state == State::Close && m_MenuBackGround->GetState() == Menu::State::Stop) {
        m_MenuBackGround->SetVisible(false);
        m_WarriorDoor->SetVisible(false);
        m_WarriorCharacter->SetVisible(false);
        m_CreateCharacter_X->SetVisible(false);
        m_NameKeyBoard->Close();
    }
    else if (state == State::Open) {
        this->SetVisible(true);
    }
}