#ifndef APP_HPP
#define APP_HPP


#include "pch.hpp" // IWYU pragma: export
#include "Util/Renderer.hpp"

class AnimatedCharacter;
class CreateCharacterMenu;
class Character;
class StartMenu;
class NewGameButton;
class NameKeyBoard;
class Map;
class Player;
class PlayerUI;

class App {
public:
    enum class State {
        START,
        UPDATE,
        END,
    };
    enum class GameState{
        START_MENU,
        ENTER_MAP,
    };

    State GetCurrentState() const { return m_CurrentState; }

    void Start();

    void Update();

    void End();

    static void AddChild(std::shared_ptr<Util::GameObject> obj) {
        m_Root.AddChild(obj);
    };
private:
    void ValidTask();

private:
    GameState m_GameState = GameState::START_MENU;
    State m_CurrentState = State::START;
    
    std::shared_ptr<AnimatedCharacter> m_StartAnime;
    std::shared_ptr<StartMenu> m_StartMenu;

    std::shared_ptr<NewGameButton> m_NewGameButton;
    std::shared_ptr<CreateCharacterMenu> m_CreateCharacterMenu;
    std::shared_ptr<Character> m_YouDied;

    std::shared_ptr<Map> m_map;
    std::shared_ptr<PlayerUI> m_UI;

    std::shared_ptr<Player> m_Player;

    static Util::Renderer m_Root;
};

#endif
