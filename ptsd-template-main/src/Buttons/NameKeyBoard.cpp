#include "Buttons/NameKeyBoard.hpp"
#include "Util/Renderer.hpp"

NameKeyBoard::NameKeyBoard(Util::Renderer *m_Root) {
    (void)m_Root;
    // char buffer[200];
    //初始化大寫字母按鈕
    // for (int i = 0; i < 26; i++) {
    //     snprintf(buffer, sizeof(buffer), RESOURCE_DIR"/Button/BigLetter/%c.png", 'A'+i);
    //     m_BigLetterBtn.emplace_back(std::make_shared<Button>(buffer));
    //     m_BigLetterBtn[i]->SetZIndex(8);
    //     m_BigLetterBtn[i]->SetPosition({-196+(i%5)*30, -13-int(i/5)*30});
    //     m_BigLetterBtn[i]->SetVisible(true);
    //     m_Root->AddChild(m_BigLetterBtn[i]);
    // }
    
    //初始化小寫字母按鈕
    // for (int i = 0; i < 26; i++) {
    //     snprintf(buffer, sizeof(buffer), RESOURCE_DIR"/Button/SmallLetter/%c.png", 'a'+i);
    //     m_SmallLetterBtn.emplace_back(std::make_shared<Button>(buffer));
    //     m_SmallLetterBtn[i]->SetZIndex(8);
    //     m_SmallLetterBtn[i]->SetPosition({-38+(i%5)*30, -13-int(i/5)*30});
    //     m_SmallLetterBtn[i]->SetVisible(true);
    //     m_Root->AddChild(m_SmallLetterBtn[i]);
    // }
}