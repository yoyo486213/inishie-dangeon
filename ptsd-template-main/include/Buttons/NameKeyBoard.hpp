#ifndef NAMEKEYBOARD_HPP
#define NAMEKEYBOARD_HPP

#include "pch.hpp"

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
    NameKeyBoard(Util::Renderer *m_Root);
    
    virtual ~NameKeyBoard() = default;

    void Open();

    void Closing();

    void Close();
    
    void Update();
private:
    std::vector<std::shared_ptr<Button>> m_BigLetterBtn;
    std::vector<std::shared_ptr<Button>> m_SmallLetterBtn;
    State state;

};

#endif //NAMEKEYBOARD_HPP