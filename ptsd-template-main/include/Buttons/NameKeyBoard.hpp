#ifndef NAMEKEYBOARD_HPP
#define NAMEKEYBOARD_HPP

#include "pch.hpp"
#include <chrono>
#include "Util/GameObject.hpp"

namespace Util {
    class Renderer;
}
class Button;

class NameKeyBoard : public Util::GameObject {
public:
    enum class State{
        Open,
        Close,
        Closing,
        Stop
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
    
    int ClickContorlBtn();

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
    State state;
    KeyBoardType Type = KeyBoardType::Eng;
    std::vector<char> output;
    std::chrono::time_point<std::chrono::high_resolution_clock> Click_time;
};

#endif //NAMEKEYBOARD_HPP