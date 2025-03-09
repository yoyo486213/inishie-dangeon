#ifndef APP_HPP
#define APP_HPP

#include "pch.hpp" // IWYU pragma: export

#include "Util/Renderer.hpp"
#include "MyBGM.hpp"
#include "Character.hpp"
#include "AnimatedCharacter.hpp"
#include "MoveCharacter.hpp"
#include "MoveAnimated.hpp"

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

    std::shared_ptr<MoveCharacter> m_NewGameBtn;
    std::shared_ptr<MyBGM> m_CreateCharacterBGM;
    std::shared_ptr<MoveCharacter> m_NewGameText;
    std::shared_ptr<MoveCharacter> m_CreateCharacter;
    std::shared_ptr<MoveAnimated> m_SkinDoor;

    
    Util::Renderer m_Root;
};

#endif
