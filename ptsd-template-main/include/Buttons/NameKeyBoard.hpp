#ifndef NAMEKEYBOARD_HPP
#define NAMEKEYBOARD_HPP

#include "pch.hpp"
#include <chrono>
#include "Util/GameObject.hpp"

namespace Util {
    class Renderer;
}
class Button;
class Text;
class MyBGM;

class NameKeyBoard : public Util::GameObject {
public:
    enum class State{
        Open,
        Close,
        Closing,
        Stop,
        GameStart,
    };
    enum class KeyBoardType{
        Eng,
        Num
    };
    NameKeyBoard(Util::Renderer *m_Root);
    
    virtual ~NameKeyBoard() = default;

    void Open();

    void Closing();

    void Close();
    
    void ToNumberType();
    void ToEnglishType();
    
    void EnableEnter() {EnterEnable = true;}
    void DisableEnter() {EnterEnable = false;}

    int ClickContorlBtn();

    std::shared_ptr<Text> GetName() { return m_Name; }

    void Update();
private:
    std::vector<std::shared_ptr<Button>> m_BigLetterBtn;
    std::vector<std::shared_ptr<Button>> m_SmallLetterBtn;
    std::vector<std::shared_ptr<Button>> m_NumberBtn;
    std::shared_ptr<Button> ToNum;
    std::shared_ptr<Button> ToEng;
    std::shared_ptr<Button> Back;
    std::shared_ptr<Button> Enter;
    std::shared_ptr<Button> Cancel;
    std::vector<std::shared_ptr<Button>> m_ControlBtn;
    State state = State::Close;
    KeyBoardType Type = KeyBoardType::Eng;
    std::vector<char> output;
    int outputIndex = 0;
    std::shared_ptr<Text> m_Name;
    std::chrono::time_point<std::chrono::high_resolution_clock> Click_time;

    bool EnterEnable = 0;

    std::shared_ptr<MyBGM> m_ButtonBGM;
};

#endif //NAMEKEYBOARD_HPP