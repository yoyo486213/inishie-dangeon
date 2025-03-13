#ifndef STARTMENU_HPP
#define STARTMENU_HPP

#include "Util/Renderer.hpp"
#include "Util/Image.hpp"
#include "Util/Animation.hpp"
#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include "Util/Logger.hpp"

#include "../Menu.hpp"
#include "../Button.hpp"
#include "../MoveAnimated.hpp"
#include "../MyBGM.hpp"

class StartMenu : public Util::GameObject{
public:
    enum class State {
        Open,
        Skip,
        Stop
    };

    StartMenu(Util::Renderer *m_Root);

    void OpenMenu();
    bool OpenButton();
    bool SkipButton();

    State GetState();
    void SetState(State State);

    void Update();

    virtual ~StartMenu() = default;
private:
    std::shared_ptr<AnimatedCharacter> m_SSslidedown;
    std::shared_ptr<AnimatedCharacter> m_SSmenu;
    State MenuState;
};

#endif //CREATECHARACTERMENU_HPP