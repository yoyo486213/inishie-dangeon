#ifndef APP_HPP
#define APP_HPP

#include "Menus/CreateCharacterMenu.hpp"
#include "pch.hpp" // IWYU pragma: export

#include "Util/Renderer.hpp"
#include "MyBGM.hpp"
#include "Character.hpp"
#include "AnimatedCharacter.hpp"
#include "Menu.hpp"
#include "Menus/CreateCharacterMenu.hpp"
#include "Button.hpp"
#include "MoveAnimated.hpp"
#include <memory>

class App {
public:
    enum class State {
        START,
        UPDATE,
        END,
    };

    State GetCurrentState() const { return m_CurrentState; }

    void Start();

    void Update();

    void End(); // NOLINT(readability-convert-member-functions-to-static)

private:
    void ValidTask();

private:
    State m_CurrentState = State::START;
    
    std::shared_ptr<AnimatedCharacter> m_SSdoor;
    std::shared_ptr<AnimatedCharacter> m_SSslidedown;
    std::shared_ptr<AnimatedCharacter> m_SSmenu;

    std::shared_ptr<Menu> m_NewGameBtn;
    std::shared_ptr<MyBGM> m_CreateCharacterOpenBGM;
    std::shared_ptr<MyBGM> m_CreateCharacterCloseBGM;
    std::shared_ptr<MyBGM> m_SkinDoorBGM;
    std::shared_ptr<Menu> m_NewGameText;
    
    std::shared_ptr<CreateCharacterMenu> m_CreateCharacterMenu;

    Util::Renderer m_Root;
};

#endif
