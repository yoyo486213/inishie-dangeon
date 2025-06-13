#include "Player.hpp"
#include "Monster/Monster.hpp"
#include "Calculation.hpp"
#include <iostream>
#include "Util/Renderer.hpp"
#include "pch.hpp"
#include "Button.hpp"

Player::Player(const std::vector<std::string> &ImagePath, Util::Renderer *m_Root) : Character(ImagePath[0]) {
    this->SetPosition({0, 0});
    this->SetVisible(true);
    this->SetZIndex(15);
    m_ImagePaths = ImagePath;
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

void Player::Update() {
    if (displacement == glm::vec2{0, 1}) {
        if (m_ImageIndex == 0) { 
            this->ChangeImage(1);
            this->m_ImageIndex = 1;
        }
        else if (m_ImageIndex == 1) {
            this->ChangeImage(0);
            this->m_ImageIndex = 0;
        }
        else {
            this->ChangeImage(0);
            this->m_ImageIndex = 0;
        }
    }
    else if (displacement == glm::vec2{0, -1}) {
        if (m_ImageIndex == 2) { 
            this->ChangeImage(3);
            this->m_ImageIndex = 3;
        }
        else if (m_ImageIndex == 3) {
            this->ChangeImage(2);
            this->m_ImageIndex = 2;
        }
        else {
            this->ChangeImage(2);
            this->m_ImageIndex = 2;
        }
    }
    else if (displacement == glm::vec2{-1, 0}) {
        if (m_ImageIndex == 4) { 
            this->ChangeImage(5);
            this->m_ImageIndex = 5;
        }
        else if (m_ImageIndex == 5) {
            this->ChangeImage(4);
            this->m_ImageIndex = 4;
        }
        else {
            this->ChangeImage(4);
            this->m_ImageIndex = 4;
        }
    }
    else if (displacement == glm::vec2{1, 0}) {
        if (m_ImageIndex == 6) { 
            this->ChangeImage(7);
            this->m_ImageIndex = 7;
        }
        else if (m_ImageIndex == 7) {
            this->ChangeImage(6);
            this->m_ImageIndex = 6;
        }
        else {
            this->ChangeImage(6);
            this->m_ImageIndex = 6;
        }
    }
}

void Player::TakeDamage(int damage) {
    m_HP -= Calculation::CalcuDmg(damage, m_Defense, m_Resistance[4]);
    if (m_HP <= 0) {
        this->SetVisible(false);
    }
}