#include "Player.hpp"
#include "Monster/Monster.hpp"
#include "Calculation.hpp"
#include <iostream>
#include "Util/Renderer.hpp"
#include "pch.hpp"
#include "Button.hpp"

Player::Player(const std::string &ImagePath, Util::Renderer *m_Root) : Character(ImagePath) {
    this->SetPosition({0, 0});
    this->SetVisible(true);
    this->SetZIndex(15);
    (void)m_Root;

    // char buffer[200];
    // std::vector<std::string> ShortcutsImages;  
    // ShortcutsImages.reserve(3);
    // for (int i = 1; i < 4; i++) {
    //     snprintf(buffer, sizeof(buffer), RESOURCE_DIR"/UI/XPBar/XPBar-%02d.png", i);
    //     ShortcutsImages.emplace_back(buffer);
    // }
    // for (int i = 0; i < 4; i++) {
    //     m_Shortcuts.emplace_back(std::make_shared<Button>(ShortcutsImages));
    //     m_Shortcuts[i]->SetZIndex(40);
    //     m_Shortcuts[i]->SetPosition({50 + 30*i, -300});
    //     m_Shortcuts[i]->SetVisible(true);
    //     m_Root->AddChild(m_Shortcuts[i]);
    // }

    // std::vector<std::string> InventoryImages;  
    // InventoryImages.reserve(3);
    // for (int i = 1; i < 4; i++) {
    //     snprintf(buffer, sizeof(buffer), RESOURCE_DIR"/UI/ItemSlot_Default.png");
    //     InventoryImages.emplace_back(buffer);
    // }
    // for (int i = 0; i < 8; i++) {
    //     m_Inventory.emplace_back(std::make_shared<Button>(InventoryImages));
    //     m_Inventory[i]->SetZIndex(40);
    //     m_Inventory[i]->SetPosition({50 + 30*i, -300});
    //     m_Inventory[i]->SetVisible(true);
    //     m_Root->AddChild(m_Inventory[i]);
    // }
}

int Player::Attack() {
    return 0;
}

void Player::Update(std::shared_ptr<Character> &m_map) {
    (void)m_map;
    // for (int i = 0; i < 4; i++)
    // {
    //     if (m_Shortcuts[i]->IfFocus()) {
    //         m_Shortcuts[i]->SetImage(RESOURCE_DIR"/UI/.png");
    //     }
    //     if (m_Shortcuts[i]->IfClick()) {
    //         m_Shortcuts[i]->SetImage(RESOURCE_DIR"/UI/.png");
    //         SelectedSlot = i;
    //     }
    // }
    // for (int i = 0; i < 8; i++)
    // {
    //     m_Inventory[i]->IfClick();
    // }
}

void Player::TakeDamage(int damage) {
    m_HP -= Calculation::CalcuDmg(damage, m_Defense, m_Resistance[4]);
    if (m_HP <= 0) {
        this->SetVisible(false);
    }
}