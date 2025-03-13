#ifndef NEWGAMEBUTTON_HPP
#define NEWGAMEBUTTON_HPP

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

class NewGameButton : public Util::GameObject{
public:
    NewGameButton(Util::Renderer *m_Root);

    bool GetClicked();

    void Open();
    void Skip();
    
    void Update();

    Menu::State GetStats();
    
    virtual ~NewGameButton() = default;
private:
    std::shared_ptr<Menu> m_NewGameBtn;
    std::shared_ptr<Menu> m_NewGameText;
};

#endif //NEWGAMEBUTTON_HPP