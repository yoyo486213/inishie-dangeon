#ifndef APP_HPP
#define APP_HPP

#include "Character.hpp"
#include "pch.hpp" // IWYU pragma: export

#include "Util/Renderer.hpp"

#include "AnimatedCharacter.hpp"
#include "Menus/CreateCharacterMenu.hpp"
#include "Menus/StartMenu.hpp"
#include "Buttons/NewGameButton.hpp"
#include "Buttons/NameKeyBoard.hpp"
#include "Map/Map.hpp"
#include <memory>

class App {
public:
    enum class State {
        START,
        UPDATE,
        END,
    };

    State GetCurrentState() const { return m_CurrentState; }

    void SetState(bool state) { this->state = state; }

    bool GetState() { return this->state; }

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
    std::shared_ptr<NameKeyBoard> m_NameKeyBoard;

    std::shared_ptr<Map> m_map;
    bool state = false;

    std::shared_ptr<Character> m_Butterfly;

    Util::Renderer m_Root;
};

#endif
