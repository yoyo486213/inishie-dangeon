#include "Buttons/NameKeyBoard.hpp"
#include "Util/Renderer.hpp"
#include "Button.hpp"

NameKeyBoard::NameKeyBoard(Util::Renderer *m_Root) {
    // (void)m_Root;
    char buffer[200];
    char buffer2[200];
    // 初始化大寫字母按鈕
    for (int i = 0; i < 26; i++) {
        snprintf(buffer, sizeof(buffer), RESOURCE_DIR"/Button/BigLetter/%c.png", 'A'+i);
        snprintf(buffer2, sizeof(buffer2), RESOURCE_DIR"/Button/BigLetter/s%c.png", 'A'+i);
        m_BigLetterBtn.emplace_back(std::make_shared<Button>(std::vector<std::string>{buffer, buffer2}));
        m_BigLetterBtn[i]->SetZIndex(8);
        m_BigLetterBtn[i]->SetPosition({-196+(i%5)*30, -13-int(i/5)*30+500});
        m_BigLetterBtn[i]->SetVisible(false);
        m_Root->AddChild(m_BigLetterBtn[i]);
    }
    
    //初始化小寫字母按鈕
    for (int i = 0; i < 26; i++) {
        
        snprintf(buffer, sizeof(buffer), RESOURCE_DIR"/Button/SmallLetter/%c.png", 'a'+i);
        snprintf(buffer2, sizeof(buffer2), RESOURCE_DIR"/Button/SmallLetter/s%c.png", 'a'+i);
        m_SmallLetterBtn.emplace_back(std::make_shared<Button>(std::vector<std::string>{buffer, buffer2}));
        m_SmallLetterBtn[i]->SetZIndex(8);
        m_SmallLetterBtn[i]->SetPosition({-38+(i%5)*30, -13-int(i/5)*30+500});
        m_SmallLetterBtn[i]->SetVisible(false);
        m_Root->AddChild(m_SmallLetterBtn[i]);
    }
}


void NameKeyBoard::Open(){
    state = State::Open;
    for (int i = 0; i < 26; i++)
    {
        m_BigLetterBtn[i]->SetVisible(true);
        m_SmallLetterBtn[i]->SetVisible(true);
    }
}
void NameKeyBoard::Closing() {
    state = State::Closing;
}
void NameKeyBoard::Close() {
    for (int i = 0; i < 26; i++)
    {
        m_BigLetterBtn[i]->SetVisible(false);
        m_SmallLetterBtn[i]->SetVisible(false);
    }
    
}


void NameKeyBoard::Update() {
    
    
    for (int i = 0; i < 26; i++)
    {
        if (m_BigLetterBtn[i]->IfFocus()) {
            m_BigLetterBtn[i]->ChangeImage(2);
            m_BigLetterBtn[i]->SetVisible(true);
        }
        else {
            m_BigLetterBtn[i]->ChangeImage(1);
        }
        
        if (state == State::Open) {
            m_BigLetterBtn[i]->Move({0, -20}, {-196+(i%5)*30, -13-int(i/5)*30});
        }
        if (state == State::Closing) {
            m_BigLetterBtn[i]->Move({0, 20}, {-196+(i%5)*30, -13-int(i/5)*30+500});
        }
    }
    
    
    for (int i = 0; i < 26; i++)
    {
        if (m_SmallLetterBtn[i]->IfFocus()) {
            m_SmallLetterBtn[i]->ChangeImage(2);
            m_SmallLetterBtn[i]->SetVisible(true);
        }
        else {
            m_SmallLetterBtn[i]->ChangeImage(1);
        }
        
        if (state == State::Open) {
            m_SmallLetterBtn[i]->Move({0, -20}, {-38+(i%5)*30, -13-int(i/5)*30});
        }
        if (state == State::Closing) {
            m_SmallLetterBtn[i]->Move({0, 20}, {-38+(i%5)*30, -13-int(i/5)*30+500});
        }
    }
}