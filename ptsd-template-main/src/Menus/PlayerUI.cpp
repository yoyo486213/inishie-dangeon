#include "Menus/PlayerUI.hpp"
#include "Util/Renderer.hpp"
#include "Util/Input.hpp"
#include "AnimatedCharacter.hpp"
#include "Text.hpp"
#include "Player.hpp"
#include "Button.hpp"
#include "Items/Item.hpp"
#include "Items/Potion.hpp"
#include "IEquipable.hpp"
#include "IUsable.hpp"
#include "Weapon/Weapon.hpp"
#include "App.hpp"

PlayerUI::PlayerUI(std::shared_ptr<Player> playerRef, std::shared_ptr<Text> NameRef, Util::Renderer *m_Root) : player(playerRef),m_Name(NameRef) {
    m_Name->SetZIndex(40);
    m_Name->SetVisible(true);

    char buffer[200];
    m_HPBox = std::make_shared<Character>(RESOURCE_DIR"/UI/HPBox.png");
    m_HPBox->SetPosition({-133 , -188});
    m_HPBox->SetVisible(true);
    m_HPBox->SetZIndex(39);
    m_Root->AddChild(m_HPBox);

    std::vector<std::string> HPImages;
    HPImages.reserve(100);
    for (int i = 1; i < 101; i++) {
        snprintf(buffer, sizeof(buffer), RESOURCE_DIR"/UI/HPBar/HPBar-%03d.png", i);
        HPImages.emplace_back(buffer);
    }
    m_HP = std::make_shared<AnimatedCharacter>(HPImages);
    m_HP->SetPosition({-117 , -188});
    m_HP->SetVisible(true);
    m_HP->SetLooping(false);
    m_HP->SetZIndex(40);
    m_Root->AddChild(m_HP);


    m_MPBox = std::make_shared<Character>(RESOURCE_DIR"/UI/MPBox.png");
    m_MPBox->SetPosition({-133 , -208});
    m_MPBox->SetVisible(true);
    m_MPBox->SetZIndex(39);
    m_Root->AddChild(m_MPBox);

    std::vector<std::string> MPImages;
    MPImages.reserve(100);
    for (int i = 1; i < 101; i++) {
        snprintf(buffer, sizeof(buffer), RESOURCE_DIR"/UI/MPBar/MPBar-%03d.png", i);
        MPImages.emplace_back(buffer);
    }
    m_MP = std::make_shared<AnimatedCharacter>(MPImages);
    m_MP->SetPosition({-116 , -208});
    m_MP->SetVisible(true);
    m_MP->SetLooping(false);
    m_MP->SetZIndex(40);
    m_Root->AddChild(m_MP);

    m_Name->SetPosition({-263+m_Name->GetScaledSize().x/2 ,193+m_Name->GetScaledSize().y/2});

    m_EXPBox = std::make_shared<Character>(RESOURCE_DIR"/UI/XPBox.png");
    m_EXPBox->SetPosition({m_Name->GetPosition().x + m_Name->GetScaledSize().x / 2 + m_EXPBox->GetScaledSize().x / 2 + 5, m_Name->GetPosition().y});
    m_EXPBox->SetVisible(true);
    m_EXPBox->SetZIndex(39);
    m_Root->AddChild(m_EXPBox);

    std::vector<std::string> EXPImages;
    EXPImages.reserve(75);
    for (int i = 1; i < 76; i++) {
        snprintf(buffer, sizeof(buffer), RESOURCE_DIR"/UI/XPBar/XPBar-%02d.png", i);
        EXPImages.emplace_back(buffer);
    }
    m_EXP = std::make_shared<AnimatedCharacter>(EXPImages);
    m_EXP->SetPosition({-130 , 208});
    m_EXP->SetCurrentFrame(74);
    m_EXP->SetVisible(true);
    m_EXP->SetLooping(false);
    m_EXP->SetZIndex(40);
    m_Root->AddChild(m_EXP);

    for (int i = 0; i < 4; i++) {
        m_Shortcuts[i] = std::make_shared<Button>(
            std::vector<std::string>{
                RESOURCE_DIR"/UI/ItemSlot_Default.png",
                RESOURCE_DIR"/UI/ItemSlot_Selected.png",
                RESOURCE_DIR"/UI/ItemSlot_Cooldown.png",
                RESOURCE_DIR"/UI/FocusItemSlot_Default.png",
                RESOURCE_DIR"/UI/FocusItemSlot_Selected.png",
                RESOURCE_DIR"/UI/FocusItemSlot_Cooldown.png"
            }
        );
        m_Shortcuts[i]->SetPosition({80 + i * 42, -194});
        m_Shortcuts[i]->SetVisible(true);
        m_Shortcuts[i]->SetZIndex(39);
        m_Root->AddChild(m_Shortcuts[i]);

        m_ShortcutsBackGrounds[i] = std::make_shared<Character>(RESOURCE_DIR"/UI/ItemSlot_BackGround.png");
        m_ShortcutsBackGrounds[i]->SetPosition({80 + i * 42, -194});
        m_ShortcutsBackGrounds[i]->SetVisible(true);
        m_ShortcutsBackGrounds[i]->SetZIndex(37);
        m_Root->AddChild(m_ShortcutsBackGrounds[i]);
    }

    for (int i = 0; i < 8; i++) {
        m_Inventory[i] = std::make_shared<Button>(
            std::vector<std::string>{
                RESOURCE_DIR"/UI/ItemSlot_NotMarked.png",
                RESOURCE_DIR"/UI/ItemSlot_Default.png",
                RESOURCE_DIR"/UI/FocusItemSlot_Default.png"
            }
        );
        if (i < 4) {
            m_Inventory[i]->SetPosition({120 + i * 42, -79});
        } 
        else {
            m_Inventory[i]->SetPosition({120 + (i - 4) * 42, -121});
        }
        m_Inventory[i]->SetVisible(true);
        m_Inventory[i]->SetZIndex(39);
        m_Root->AddChild(m_Inventory[i]);
    }

    m_Backpack = std::make_shared<Button>(
        std::vector<std::string>{
            RESOURCE_DIR"/UI/Backpack_Default.png",
            RESOURCE_DIR"/UI/Backpack_Focus.png",
            RESOURCE_DIR"/UI/Backpack_Open.png"
        }
    );
    m_Backpack->SetPosition({258, -194});
    m_Backpack->SetVisible(true);
    m_Backpack->SetZIndex(39);
    m_Root->AddChild(m_Backpack);

    m_CloseButton = std::make_shared<Button>(
        std::vector<std::string>{
            RESOURCE_DIR"/UI/Backpack_X.png",
            RESOURCE_DIR"/UI/Backpack_X_Focus.png",
            RESOURCE_DIR"/UI/Backpack_X_Pressed.png"
        }
    );
    m_CloseButton->SetPosition({275, -45});
    m_CloseButton->SetVisible(false);
    m_CloseButton->SetZIndex(39);
    m_Root->AddChild(m_CloseButton);

    m_BackpackBackGround = std::make_shared<Character>(RESOURCE_DIR"/UI/Backpack_BackGround.png");
    m_BackpackBackGround->SetPosition({183, -100});
    m_BackpackBackGround->SetVisible(true);
    m_BackpackBackGround->SetZIndex(37);
    m_Root->AddChild(m_BackpackBackGround);
}

bool PlayerUI::PeekItem(std::shared_ptr<Item> item) {
    for (int i=0; i<4; i++) {
        if (!m_ShortcutsItems[i]) {
            m_ShortcutsItems[i] = item;
            item->SetPosition(m_Shortcuts[i]->GetPosition());
            item->SetZIndex(40);
            return true;
        }
    }

    for (int i=0; i<8; i++) {
        if (!m_InventoryItems[i]) {
            m_InventoryItems[i] = item;
            item->SetPosition(m_Inventory[i]->GetPosition());
            item->SetZIndex(40);
            if (m_Backpack->GetImageIndex() != 3) {
                item->SetVisible(false);
            }
            return true;
        }
    }
    return false;
}


void PlayerUI::RejoinRander(Util::Renderer *m_Root){
    m_Root->AddChild(m_Name);
    m_Root->AddChild(m_HPBox);
    m_Root->AddChild(m_HP);
    m_Root->AddChild(m_MPBox);
    m_Root->AddChild(m_MP);
    m_Root->AddChild(m_EXPBox);
    m_Root->AddChild(m_EXP);
    for (int i = 0; i < 4; i++) {
        m_Root->AddChild(m_Shortcuts[i]);
        m_Root->AddChild(m_ShortcutsBackGrounds[i]);
        if (m_ShortcutsItems[i]) {
            m_Root->AddChild(m_ShortcutsItems[i]);
        }
        
    }
    for (int i = 0; i < 8; i++) {
        m_Root->AddChild(m_Inventory[i]);
        if (m_InventoryItems[i]) {
            m_Root->AddChild(m_InventoryItems[i]);
        }
    }
    m_Root->AddChild(m_Backpack);
    m_Root->AddChild(m_BackpackBackGround);
    m_Root->AddChild(m_CloseButton);
}



void PlayerUI::Update(std::shared_ptr<Player> &m_Player, Util::Renderer *m_Root) {
    int HPRate=float(player->GetHP())/float(player->GetMaxHP())*100;
    if (HPRate >= 1)
        m_HP->SetCurrentFrame(HPRate-1);
    else
        m_HP->SetCurrentFrame(HPRate);

    int MPRate=float(player->GetMP())/float(player->GetMaxMP())*100;
    if (MPRate != 0)
        m_MP->SetCurrentFrame(MPRate-1);
    else
        m_MP->SetCurrentFrame(MPRate);

    int expRate=float(player->GetExp())/float(player->GetMaxExp())*75;
    if (expRate != 0)
        m_EXP->SetCurrentFrame(expRate-1);
    else {
        m_EXP->SetCurrentFrame(expRate);
    }


    if (m_Backpack->IfClick()) {
        if (m_Backpack->GetImageIndex() == 3) {
            m_Backpack->ChangeImage(2);
            m_CloseButton->SetVisible(false);

            for (int i = 0; i < 8; i++) {
                m_Inventory[i]->ChangeImage(1);
                if (m_InventoryItems[i]) {
                    m_InventoryItems[i]->SetVisible(false);
                }
            }
        }
        else { // 打開
            m_Backpack->ChangeImage(3);
            m_CloseButton->SetVisible(true);

            for (int i = 0; i < 8; i++) {
                m_Inventory[i]->ChangeImage(2);
                if (m_InventoryItems[i]) {
                    m_InventoryItems[i]->SetVisible(true);
                }
            }
        }
    }
    else if (m_Backpack->IfFocus() && m_Backpack->GetImageIndex() != 3) {
        m_Backpack->ChangeImage(2);
        m_BackpackBackGround->SetVisible(true);

        for (int i = 0; i < 8; i++) {
            m_Inventory[i]->SetVisible(true);
            m_Inventory[i]->ChangeImage(2);
            if (m_InventoryItems[i]) {
                m_InventoryItems[i]->SetVisible(true);
            }
        }
    }
    else if (m_Backpack->GetImageIndex() != 3) {
        m_Backpack->ChangeImage(1);
        m_BackpackBackGround->SetVisible(false);

        for (int i = 0; i < 8; i++) {
            m_Inventory[i]->SetVisible(false);
            m_Inventory[i]->ChangeImage(1);
            if (m_InventoryItems[i]) {
                m_InventoryItems[i]->SetVisible(false);
            }
        }
    }

    if (m_CloseButton->IfClick()) {
        m_Backpack->ChangeImage(1);
        m_CloseButton->SetVisible(false);
        m_BackpackBackGround->SetVisible(false);

        for (int i = 0; i < 8; i++) {
            m_Inventory[i]->SetVisible(false);
            if (m_InventoryItems[i]) {
                m_InventoryItems[i]->SetVisible(false);
            }
            m_Inventory[i]->ChangeImage(1);
        }
    }
    else if (m_CloseButton->IfPressed()) {
        m_CloseButton->ChangeImage(3);
    }
    else if (m_CloseButton->IfFocus()) {
        m_CloseButton->ChangeImage(2);
    }
    else {
        m_CloseButton->ChangeImage(1);
    }

    for (int i = 0; i < 8; i++) {
        if (m_Inventory[i]->IfClick() && m_InventoryItems[i]) {
            for (int j = 0; j < 4; j++) {
                if (!m_ShortcutsItems[j]) {
                    m_ShortcutsItems[j] = m_InventoryItems[i];
                    m_ShortcutsItems[j]->SetPosition(m_Shortcuts[j]->GetPosition());
                    m_InventoryItems[i] = nullptr;
                    break;
                    // 進背包後要CD
                }
            }
        }
        else if (m_Inventory[i]->IfFocus()) {
            m_Inventory[i]->ChangeImage(3);
        }
        else if (m_Backpack->GetImageIndex() == 3) {
            m_Inventory[i]->ChangeImage(2);
        }
        else {
            m_Inventory[i]->ChangeImage(1);
        }
    }

    Util::Keycode keycodes[] = {
    Util::Keycode::NUM_1,
    Util::Keycode::NUM_2,
    Util::Keycode::NUM_3,
    Util::Keycode::NUM_4
    };

    for (int i = 0; i < 4; ++i) {
        if ((Util::Input::IsKeyDown(keycodes[i]) || m_Shortcuts[i]->IfClick()) && m_ShortcutsItems[i]) {
            // if (this->SelectedSlot == -1) {
                if (auto e = std::dynamic_pointer_cast<IEquipable>(m_ShortcutsItems[i])) {
                    e->Equip();
                }
                if (auto u = std::dynamic_pointer_cast<IUsable>(m_ShortcutsItems[i])) {
                    if (u->Use()) { // 只有當 Use() 回 true 時才移除
                        m_Root->RemoveChild(m_ShortcutsItems[i]);
                        m_ShortcutsItems[i] = nullptr;
                    }
                }
            // }
            // else {
            //     if (auto e = std::dynamic_pointer_cast<IEquipable>(m_ShortcutsItems[i])) {
            //         e->UnEquip(m_Player);
            //     }
            // }
        }
    }
    
    for (int i = 0; i < 4; i++) {
        if ((Util::Input::IsKeyDown(keycodes[i]) || m_Shortcuts[i]->IfClick()) && m_ShortcutsItems[i]) {
            if (m_Shortcuts[i]->GetImageIndex() == 2 || m_Shortcuts[i]->GetImageIndex() == 5) {
                m_Shortcuts[i]->ChangeImage(1);
                SelectedSlot = -1;
            }
            else {
                m_Shortcuts[i]->ChangeImage(5);
                SelectedSlot = i;
            }

            for (int j = 0; j < 4; j++) {
                if (j != i) {
                    m_Shortcuts[j]->ChangeImage(1);
                }
            }
        }
        else if (m_Shortcuts[i]->IfFocus()) {
            if (m_Shortcuts[i]->GetImageIndex() <= 3) {
                m_Shortcuts[i]->ChangeImage(m_Shortcuts[i]->GetImageIndex() + 3);
            }
        }
        else if (m_Shortcuts[i]->GetImageIndex() > 3) {
            m_Shortcuts[i]->ChangeImage(m_Shortcuts[i]->GetImageIndex() - 3);
        }
    }

    if (Util::Input::IsKeyDown(Util::Keycode::MOUSE_LB) && m_ShortcutsItems[SelectedSlot]) {
        if (auto u = std::dynamic_pointer_cast<IUsable>(m_ShortcutsItems[SelectedSlot])) {
            if (u->Use()) { // 只有當 Use() 回 true 時才移除
                m_Root->RemoveChild(m_ShortcutsItems[SelectedSlot]);
                m_ShortcutsItems[SelectedSlot] = nullptr;
            }
        }
    }
}

