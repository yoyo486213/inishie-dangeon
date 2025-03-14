#ifndef APP_HPP
#define APP_HPP

#include "pch.hpp" // IWYU pragma: export

#include "Util/Renderer.hpp"

#include "AnimatedCharacter.hpp"
#include "Menus/CreateCharacterMenu.hpp"
#include "Menus/StartMenu.hpp"
#include "Buttons/NewGameButton.hpp"

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
    
    std::shared_ptr<AnimatedCharacter> m_StartAnime;
    std::shared_ptr<StartMenu> m_StartMenu;

    std::shared_ptr<NewGameButton> m_NewGameButton;
    std::shared_ptr<CreateCharacterMenu> m_CreateCharacterMenu;

    Util::Renderer m_Root;
};

#endif
