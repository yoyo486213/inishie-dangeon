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
class Item;
class Button;

class PlayerUI {
public:

    PlayerUI(std::shared_ptr<Player> playerRef, std::shared_ptr<Text> NameRef, Util::Renderer *m_Root);

    virtual ~PlayerUI() = default;

    void Update(Util::Renderer *m_Root);

    bool PeekItem(std::shared_ptr<Item> item);
private:
    std::shared_ptr<Player> player;

    std::shared_ptr<Text> m_Name;

    std::shared_ptr<Character> m_HPBox;
    std::shared_ptr<Character> m_MPBox;
    std::shared_ptr<Character> m_EXPBox;

    std::shared_ptr<AnimatedCharacter> m_HP;
    std::shared_ptr<AnimatedCharacter> m_MP;
    std::shared_ptr<AnimatedCharacter> m_EXP;

    std::shared_ptr<Button> m_Backpack;
    std::shared_ptr<Character> m_BackpackBackGround;
    std::shared_ptr<Button> m_CloseButton;
    int SelectedSlot = -1;
    std::vector<std::shared_ptr<Item>> m_ShortcutsItems{4, nullptr}; // 4 格
    std::vector<std::shared_ptr<Button>> m_Shortcuts{4, nullptr}; // 4 格
    std::vector<std::shared_ptr<Character>> m_ShortcutsBackGrounds{4, nullptr}; // 4 格
    std::vector<std::shared_ptr<Item>> m_InventoryItems{8, nullptr}; // 8 格
    std::vector<std::shared_ptr<Button>> m_Inventory{8, nullptr}; // 8 格
};

#endif //PLAYERUI_HPP

//   O      O         O
//   |v   o-|     --┐-|
//   ^      ^         ^
//  / \    / \       / \  