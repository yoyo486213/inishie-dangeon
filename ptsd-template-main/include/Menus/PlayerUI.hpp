#ifndef PLAYERUI_HPP
#define PLAYERUI_HPP

#include "pch.hpp"
#include "Character.hpp"

namespace Util {
    class Renderer;
}
class AnimatedCharacter;
class Menu;
class Player;
class Text;

class PlayerUI {
public:

    PlayerUI(std::shared_ptr<Player> playerRef, std::shared_ptr<Text> NameRef, Util::Renderer *m_Root);

    virtual ~PlayerUI() = default;

    void Update();
private:
    std::shared_ptr<Player> player;

    std::shared_ptr<Text> m_Name;

    std::shared_ptr<Character> m_HPBox;
    std::shared_ptr<Character> m_MPBox;
    std::shared_ptr<Character> m_EXPBox;

    std::shared_ptr<AnimatedCharacter> m_HP;
    std::shared_ptr<AnimatedCharacter> m_MP;
    std::shared_ptr<AnimatedCharacter> m_EXP;
};

#endif //PLAYERUI_HPP