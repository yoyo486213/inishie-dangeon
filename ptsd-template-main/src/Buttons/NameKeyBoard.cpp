#include "Buttons/NameKeyBoard.hpp"
#include "Util/Renderer.hpp"
#include "TextGenerator/imageGenerator.hpp"
#include "Button.hpp"
#include "Text.hpp"
#include "MyBGM.hpp"
#include <iostream>
#include <time.h>

NameKeyBoard::NameKeyBoard(Util::Renderer *m_Root) {
    // (void)m_Root;
    char buffer[200];
    char buffer2[200];
    // 初始化大寫字母按鈕
    for (int i = 0; i < 26; i++) {
        snprintf(buffer, sizeof(buffer), RESOURCE_DIR"/Button/NameKeyBoard/BigLetter/%c.png", 'A'+i);
        snprintf(buffer2, sizeof(buffer2), RESOURCE_DIR"/Button/NameKeyBoard/BigLetter/s%c.png", 'A'+i);
        m_BigLetterBtn.emplace_back(std::make_shared<Button>(std::vector<std::string>{buffer, buffer2}));
        m_BigLetterBtn[i]->SetZIndex(8);
        m_BigLetterBtn[i]->SetPosition({-196+(i%5)*30, -13-int(i/5)*30+500});
        m_BigLetterBtn[i]->SetVisible(false);
        m_Root->AddChild(m_BigLetterBtn[i]);
    }
    
    //初始化小寫字母按鈕
    for (int i = 0; i < 26; i++) {
        
        snprintf(buffer, sizeof(buffer), RESOURCE_DIR"/Button/NameKeyBoard/SmallLetter/%c.png", 'a'+i);
        snprintf(buffer2, sizeof(buffer2), RESOURCE_DIR"/Button/NameKeyBoard/SmallLetter/s%c.png", 'a'+i);
        m_SmallLetterBtn.emplace_back(std::make_shared<Button>(std::vector<std::string>{buffer, buffer2}));
        m_SmallLetterBtn[i]->SetZIndex(8);
        m_SmallLetterBtn[i]->SetPosition({-38+(i%5)*30, -13-int(i/5)*30+500});
        m_SmallLetterBtn[i]->SetVisible(false);
        m_Root->AddChild(m_SmallLetterBtn[i]);
    }
    
    //初始化數字按鈕
    for (int i = 0; i < 10; i++) {
        snprintf(buffer, sizeof(buffer), RESOURCE_DIR"/Button/NameKeyBoard/Number/%c.png", '0'+i);
        snprintf(buffer2, sizeof(buffer2), RESOURCE_DIR"/Button/NameKeyBoard/Number/s%c.png", '0'+i);
        m_NumberBtn.emplace_back(std::make_shared<Button>(std::vector<std::string>{buffer, buffer2}));
        m_NumberBtn[i]->SetZIndex(8);
        m_NumberBtn[i]->SetPosition({-196+int(i/5)*158+(i%5)*30, -13+500});
        m_NumberBtn[i]->SetVisible(false);
        m_Root->AddChild(m_NumberBtn[i]);
    }
    //初始化控制按鈕
    snprintf(buffer, sizeof(buffer), RESOURCE_DIR"/Button/NameKeyBoard/0123.png");
    snprintf(buffer2, sizeof(buffer2), RESOURCE_DIR"/Button/NameKeyBoard/s0123.png");
    ToNum = (std::make_shared<Button>(std::vector<std::string>{buffer, buffer2}));   
    ToNum->SetZIndex(8);
    ToNum->SetPosition({122+ToNum->GetScaledSize().x/2, -38+500});
    ToNum->SetVisible(false);
    m_Root->AddChild(ToNum);
    snprintf(buffer, sizeof(buffer), RESOURCE_DIR"/Button/NameKeyBoard/ABC.png");
    snprintf(buffer2, sizeof(buffer2), RESOURCE_DIR"/Button/NameKeyBoard/sABC.png");
    ToEng = (std::make_shared<Button>(std::vector<std::string>{buffer, buffer2}));   
    ToEng->SetZIndex(8);
    ToEng->SetPosition({122+ToEng->GetScaledSize().x/2, -38+500});
    ToEng->SetVisible(false);
    m_Root->AddChild(ToEng);
    snprintf(buffer, sizeof(buffer), RESOURCE_DIR"/Button/NameKeyBoard/Back.png");
    snprintf(buffer2, sizeof(buffer2), RESOURCE_DIR"/Button/NameKeyBoard/sBack.png");
    Back = (std::make_shared<Button>(std::vector<std::string>{buffer, buffer2}));   
    Back->SetZIndex(8);
    Back->SetPosition({122+Back->GetScaledSize().x/2, -73-0*35+500});
    Back->SetVisible(false);
    m_ControlBtn.emplace_back(Back);
    m_Root->AddChild(Back);
    snprintf(buffer, sizeof(buffer), RESOURCE_DIR"/Button/NameKeyBoard/Enter.png");
    snprintf(buffer2, sizeof(buffer2), RESOURCE_DIR"/Button/NameKeyBoard/sEnter.png");
    Enter = (std::make_shared<Button>(std::vector<std::string>{buffer, buffer2}));    
    Enter->SetZIndex(8);
    Enter->SetPosition({122+Enter->GetScaledSize().x/2, -73-1*35+500});
    Enter->SetVisible(false);
    m_ControlBtn.emplace_back(Enter);
    m_Root->AddChild(Enter);
    snprintf(buffer, sizeof(buffer), RESOURCE_DIR"/Button/NameKeyBoard/Cancel.png");
    snprintf(buffer2, sizeof(buffer2), RESOURCE_DIR"/Button/NameKeyBoard/sCancel.png");
    Cancel = (std::make_shared<Button>(std::vector<std::string>{buffer, buffer2}));    
    Cancel->SetZIndex(8);
    Cancel->SetPosition({122+Cancel->GetScaledSize().x/2, -73-2*35+500});
    Cancel->SetVisible(false);
    m_ControlBtn.emplace_back(Cancel);
    m_Root->AddChild(Cancel);

    //初始化BGM
    m_ButtonBGM = std::make_shared<MyBGM>(RESOURCE_DIR"/BGM/MenuOpenSnd.wav");

    m_Name = std::make_shared<Text>(RESOURCE_DIR"/Text/space.png");
    m_Name->SetZIndex(8);
    m_Name->SetPosition({-3.5, 50});
    m_Name->SetVisible(false);
    m_Root->AddChild(m_Name);
}

void NameKeyBoard::Open(){
    state = State::Open;
    if (Type == KeyBoardType::Eng) {
        ToNum->SetVisible(true);
        for (int i = 0; i < 26; i++)
        {
            m_BigLetterBtn[i]->SetVisible(true);
            m_SmallLetterBtn[i]->SetVisible(true);
        }
    }
    else {
        ToEng->SetVisible(true);
        for (int i = 0; i < 10; i++)
        {
            m_NumberBtn[i]->SetVisible(true);
        }
    }
    Back->SetVisible(true);
    Cancel->SetVisible(true);
    Enter->SetVisible(true);
    m_Name->SetVisible(true);
}
void NameKeyBoard::Closing() {
    state = State::Closing;
}
void NameKeyBoard::Close() {
    if (state == State::GameStart) {
        for (int i = 0; i < 26; i++) {
            m_BigLetterBtn[i]->SetVisible(false);
            m_SmallLetterBtn[i]->SetVisible(false);
        }
        for (int i = 0; i < 10; i++) {
            m_NumberBtn[i]->SetVisible(false);
        }
        if (Type == KeyBoardType::Eng)
            ToNum->SetVisible(false);
        else
            ToEng->SetVisible(false);
        Back->SetVisible(false);
        Cancel->SetVisible(false);
        Enter->SetVisible(false);
        if (state != State::GameStart) {
            m_Name->SetVisible(false);
        }
        Type = KeyBoardType::Eng;
        state = State::Close;
    }
}


void NameKeyBoard::ToNumberType() {
    Type = KeyBoardType::Num;
    ToNum->SetVisible(false);
    for (int i = 0; i < 26; i++)
    {
        m_BigLetterBtn[i]->SetVisible(false);
        m_SmallLetterBtn[i]->SetVisible(false);
    }
    for (int i = 0; i < 10; i++)
    {
        m_NumberBtn[i]->SetVisible(true);
    }
    ToEng->SetVisible(true);
}

void NameKeyBoard::ToEnglishType() {
    Type = KeyBoardType::Eng;
    ToEng->SetVisible(false);
    for (int i = 0; i < 26; i++)
    {
        m_BigLetterBtn[i]->SetVisible(true);
        m_SmallLetterBtn[i]->SetVisible(true);
    }
    for (int i = 0; i < 10; i++)
    {
        m_NumberBtn[i]->SetVisible(false);
    }
    ToNum->SetVisible(true);
}


int NameKeyBoard::ClickContorlBtn() {
    for (int i = 1; i < 3; i++) {
        if (m_ControlBtn[i]->IfClick()) {
            m_ButtonBGM->Play(0);
            return i+1;
        }
    }
    return 0;
}


void NameKeyBoard::Update() {
    for (int i = 0; i < 26; i++)
    {
        if (m_BigLetterBtn[i]->IfFocus()) {
            m_BigLetterBtn[i]->ChangeImage(2);
            m_BigLetterBtn[i]->SetVisible(true);
            auto duration = (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - Click_time));
            if (duration.count() > 50) {
                if (m_BigLetterBtn[i]->IfClick()) {
                    m_ButtonBGM->Play(0);
                    Click_time = std::chrono::high_resolution_clock::now();
                    if (output.size()<11)
                        output.push_back('A'+i);
                    else {
                        output.pop_back();
                        output.push_back('A'+i);
                    }
                    std::string outputString(output.begin(), output.end());
                    ImageGenerator::GenImage(outputString, outputIndex);
                    m_Name->SetImage(RESOURCE_DIR"/TextGenerator/output" + std::to_string(outputIndex) + ".png");
                    outputIndex+=1;
                }
            }
        }
        else {
            m_BigLetterBtn[i]->ChangeImage(1);
        }
    }
    
    
    for (int i = 0; i < 26; i++)
    {
        if (m_SmallLetterBtn[i]->IfFocus()) {
            m_SmallLetterBtn[i]->ChangeImage(2);
            m_SmallLetterBtn[i]->SetVisible(true);
            auto duration = (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - Click_time));
            if (duration.count() > 50) {
                if (m_SmallLetterBtn[i]->IfClick()) {
                    m_ButtonBGM->Play(0);
                    Click_time = std::chrono::high_resolution_clock::now();
                    if (output.size()<11)
                        output.push_back('a'+i);
                    else {
                        output.pop_back();
                        output.push_back('a'+i);
                    }
                    std::string outputString(output.begin(), output.end());
                    ImageGenerator::GenImage(outputString, outputIndex);
                    m_Name->SetImage(RESOURCE_DIR"/TextGenerator/output" + std::to_string(outputIndex) + ".png");
                    outputIndex+=1;
                }
            }
        }
        else {
            m_SmallLetterBtn[i]->ChangeImage(1);
        }
    }

    for (int i = 0; i < 10; i++)
    {
        if (m_NumberBtn[i]->IfFocus()) {
            m_NumberBtn[i]->ChangeImage(2);
            m_NumberBtn[i]->SetVisible(true);
            auto duration = (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - Click_time));
            if (duration.count() > 50) {
                if (m_NumberBtn[i]->IfClick()) {
                    m_ButtonBGM->Play(0);
                    Click_time = std::chrono::high_resolution_clock::now();
                    if (output.size()<11)
                        output.push_back('0'+i);
                    else {
                        output.pop_back();
                        output.push_back('0'+i);
                    }
                    std::string outputString(output.begin(), output.end());
                    ImageGenerator::GenImage(outputString, outputIndex);
                    m_Name->SetImage(RESOURCE_DIR"/TextGenerator/output" + std::to_string(outputIndex) + ".png");
                    outputIndex+=1;
                }
            }
        }
        else {
            m_NumberBtn[i]->ChangeImage(1);
        }
    }

    for (int i = 0; i < 3; i++)
    {
        if (m_ControlBtn[i]->IfFocus()) {
            m_ControlBtn[i]->ChangeImage(2);
            m_ControlBtn[i]->SetVisible(true);
        }
        else {
            m_ControlBtn[i]->ChangeImage(1);
        }
        auto duration = (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - Click_time));
        if (duration.count() > 50) {
            if (m_ControlBtn[0]->IfClick()) {
                m_ButtonBGM->Play(0);
                Click_time = std::chrono::high_resolution_clock::now();
                if (output.size()>0)
                    output.pop_back();
                
                std::string outputString(output.begin(), output.end());
                ImageGenerator::GenImage(outputString, outputIndex);
                m_Name->SetImage(RESOURCE_DIR"/TextGenerator/output" + std::to_string(outputIndex) + ".png");
                outputIndex+=1;
            }
            if (m_ControlBtn[1]->IfClick()) {
                state = State::GameStart;
            }
            if (m_ControlBtn[2]->IfClick()) {
                Click_time = std::chrono::high_resolution_clock::now();
                output.clear();
                std::string outputString(output.begin(), output.end());
                ImageGenerator::GenImage(outputString, outputIndex);
                m_Name->SetImage(RESOURCE_DIR"/TextGenerator/output" + std::to_string(outputIndex) + ".png");
                outputIndex+=1;
            }
        }
        
    }

    if (Type == KeyBoardType::Eng) {
        if (ToNum->IfFocus()) {
            ToNum->ChangeImage(2);
            ToNum->SetVisible(true);
        }
        else {
            ToNum->ChangeImage(1);
        }auto duration = (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - Click_time));
        if (duration.count() > 50) {
            if (ToNum->IfClick()) {
                m_ButtonBGM->Play(0);
                Click_time = std::chrono::high_resolution_clock::now();
                this->ToNumberType();
            }
        }
        
    }
    else {
        if (ToEng->IfFocus()) {
            ToEng->ChangeImage(2);
            ToEng->SetVisible(true);
        }
        else {
            ToEng->ChangeImage(1);
        }
        if (ToEng->IfClick()) {
            m_ButtonBGM->Play(0);
            auto duration = (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - Click_time));
            if (duration.count() > 50) {
                Click_time = std::chrono::high_resolution_clock::now();
                this->ToEnglishType();
            }
        }
    }
    

    if (state == State::Open) {
        for (int i = 0; i < 26; i++) {
            m_BigLetterBtn[i]->Move({0, -20}, {-196+(i%5)*30, -13-int(i/5)*30});
            m_SmallLetterBtn[i]->Move({0, -20}, {-38+(i%5)*30, -13-int(i/5)*30});
        }
        for (int i = 0; i < 10; i++) 
            m_NumberBtn[i]->Move({0, -20}, {-196+int(i/5)*158+(i%5)*30, -13});
        
        for (int i = 0; i < 3; i++)
            m_ControlBtn[i]->Move({0, -20}, {122+m_ControlBtn[i]->GetScaledSize().x/2, -73-i*35});
        
        ToNum->Move({0, -20}, {122+ToNum->GetScaledSize().x/2, -38});
        ToEng->Move({0, -20}, {122+ToEng->GetScaledSize().x/2, -38});
        m_Name->Move({0, -20}, {-3.5, 50});
    }

    if (state == State::Closing) {
        for (int i = 0; i < 26; i++) {
            m_BigLetterBtn[i]->Move({0, 20}, {-196+(i%5)*30, -13-int(i/5)*30+500});
            m_SmallLetterBtn[i]->Move({0, 20}, {-38+(i%5)*30, -13-int(i/5)*30+500});
        }
        for (int i = 0; i < 10; i++) 
            m_NumberBtn[i]->Move({0, 20}, {-196+int(i/5)*158+(i%5)*30, -13+500});
        for (int i = 0; i < 3; i++)
            m_ControlBtn[i]->Move({0, 20}, {122+m_ControlBtn[i]->GetScaledSize().x/2, -73-i*35+500});

        ToNum->Move({0, 20}, {122+ToNum->GetScaledSize().x/2, -38+500});
        ToEng->Move({0, 20}, {122+ToEng->GetScaledSize().x/2, -38+500});
        if (state != State::GameStart)
            m_Name->Move({0, 20}, {-3.5, 50+500});
    }
    
}