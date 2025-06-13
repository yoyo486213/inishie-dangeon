#ifndef PLAYERUI_HPP
#define PLAYERUI_HPP

#include "pch.hpp"
#include "Character.hpp"
#include "Weapon/Weapon.hpp"
#include <chrono>

namespace Util {
    class Renderer;
}
class AnimatedCharacter;
class Menu;
class Player;
class Text;
class Item;
class Button;
class Map;

class PlayerUI {
public:
    enum class MouseActionState {
        Idle,
        Pressed,
        Dragging,
        Released
    };

    PlayerUI(std::shared_ptr<Map> MapRef, std::shared_ptr<Player> playerRef, std::shared_ptr<Text> NameRef, Util::Renderer *m_Root);

    virtual ~PlayerUI() = default;

    void Update(std::shared_ptr<Player> &m_Player, Util::Renderer *m_Root);

    bool PeekItem(std::shared_ptr<Item> item);

    void RejoinRander(Util::Renderer *m_Root);

    bool IsEquip() { return SelectedSlot != -1; }

    void DropItem();
    
    void SwapItem(int from, int to);

    void DraggingItem();

    std::shared_ptr<Weapon> GetWeapon() { return std::dynamic_pointer_cast<Weapon>(m_ShortcutsItems[SelectedSlot]); }

    float GetSkillCD() const { return m_SkillCD; }
    void SetSkillCD(float skillCD) { m_SkillCD = skillCD; }
private:
    std::shared_ptr<Map> map;
    std::shared_ptr<Player> player;
    std::chrono::time_point<std::chrono::high_resolution_clock> Click_time;
    bool Click_Btn = 0;

    MouseActionState m_MouseState = MouseActionState::Idle;
    std::shared_ptr<Item> m_DraggingItem = nullptr;
    int m_DraggingFromSlot = -1;
    int m_CurrentPressingIndex;
    bool m_Pressing = false;
    std::shared_ptr<Text> m_Name;

    std::shared_ptr<Character> m_HPBox;
    std::shared_ptr<Character> m_MPBox;
    std::shared_ptr<Character> m_EXPText;
    std::shared_ptr<Text> m_LevelTensDigits;
    std::shared_ptr<Text> m_LevelSingleDigits;
    std::shared_ptr<Character> m_EXPBox;
    std::vector<std::string> ExpImages = {RESOURCE_DIR"/Text/Number/0.png", RESOURCE_DIR"/Text/Number/1.png",
                                            RESOURCE_DIR"/Text/Number/2.png", RESOURCE_DIR"/Text/Number/3.png",
                                            RESOURCE_DIR"/Text/Number/4.png", RESOURCE_DIR"/Text/Number/5.png", 
                                            RESOURCE_DIR"/Text/Number/6.png", RESOURCE_DIR"/Text/Number/7.png",
                                            RESOURCE_DIR"/Text/Number/8.png", RESOURCE_DIR"/Text/Number/9.png"};

    std::shared_ptr<AnimatedCharacter> m_HP;
    std::shared_ptr<AnimatedCharacter> m_MP;
    std::shared_ptr<AnimatedCharacter> m_EXP;

    std::shared_ptr<Button> m_Backpack;
    std::shared_ptr<Character> m_BackpackBackGround;
    std::shared_ptr<Button> m_CloseButton;
    int SelectedSlot = -1;
    float m_SkillCD;
    std::shared_ptr<Character> m_SelectedBlockBox;
    

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