#ifndef STARTMENU_HPP
#define STARTMENU_HPP

#include "pch.hpp"
#include "Util/GameObject.hpp"

namespace Util {
    class Renderer;
}
class AnimatedCharacter;

class StartMenu : public Util::GameObject{
public:
    enum class State {
        Open,
        Skip,
        Stop
    };

    StartMenu(Util::Renderer *m_Root);
    
    virtual ~StartMenu() = default;
    
    void Update();

    void OpenMenu();

    bool OpenButton();

    bool SkipButton();

    State GetState() { return MenuState; }

    void SetState(State State) { MenuState = State; }

private:
    State MenuState;
    std::shared_ptr<AnimatedCharacter> m_SSslidedown;
    std::shared_ptr<AnimatedCharacter> m_SSmenu;
};

#endif //CREATECHARACTERMENU_HPP