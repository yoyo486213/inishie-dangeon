#include "Menus/PlayerUI.hpp"
#include "Util/Renderer.hpp"
#include "Util/Input.hpp"
#include "Util/Time.hpp"
#include "AnimatedCharacter.hpp"
#include "Text.hpp"
#include "Player.hpp"
#include "Button.hpp"
#include "Items/Item.hpp"
#include "Items/Potion.hpp"
#include "IEquipable.hpp"
#include "IUsable.hpp"
#include "Util/Time.hpp"
#include "Weapon/Weapon.hpp"
#include "App.hpp"
#include "Map/Map.hpp"
#include <iostream>

PlayerUI::PlayerUI(std::shared_ptr<Map> MapRef, std::shared_ptr<Player> playerRef, std::shared_ptr<Text> NameRef, Util::Renderer *m_Root) : map(MapRef),player(playerRef),m_Name(NameRef) {
    Click_time = std::chrono::high_resolution_clock::now();
    int leftdownmove = -75;
    
    m_Name->SetZIndex(40);
    m_Name->SetVisible(true);
    m_Name->SetPosition({-283+m_Name->GetScaledSize().x/2 ,190+m_Name->GetScaledSize().y/2});

    char buffer[200];
    m_HPBox = std::make_shared<Character>(RESOURCE_DIR"/UI/HPBox.png");
    m_HPBox->SetPosition({-133 + leftdownmove, -188});
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
    m_HP->SetPosition({-117 + leftdownmove, -188});
    m_HP->SetVisible(true);
    m_HP->SetLooping(false);
    m_HP->SetZIndex(40);
    m_Root->AddChild(m_HP);


    m_MPBox = std::make_shared<Character>(RESOURCE_DIR"/UI/MPBox.png");
    m_MPBox->SetPosition({-133 + leftdownmove, -208});
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
    m_MP->SetPosition({-116 + leftdownmove, -208});
    m_MP->SetVisible(true);
    m_MP->SetLooping(false);
    m_MP->SetZIndex(40);
    m_Root->AddChild(m_MP);

    m_EXPText = std::make_shared<Character>(RESOURCE_DIR"/UI/Lv.png");
    m_EXPText->SetPosition({m_Name->GetPosition().x + m_Name->GetScaledSize().x / 2 + 20, m_Name->GetPosition().y});
    m_EXPText->SetVisible(true);
    m_EXPText->SetZIndex(39);
    m_Root->AddChild(m_EXPText);

    m_LevelTensDigits = std::make_shared<Text>(ExpImages[(int)(player->GetLevel() / 10)]);
    m_LevelTensDigits->SetPosition({m_EXPText->GetPosition().x + 25, m_Name->GetPosition().y});
    m_LevelTensDigits->SetVisible(false);
    m_LevelTensDigits->SetZIndex(39);
    m_Root->AddChild(m_LevelTensDigits);

    m_LevelSingleDigits = std::make_shared<Text>(ExpImages[player->GetLevel() % 10]);
    m_LevelSingleDigits->SetPosition({m_EXPText->GetPosition().x + 25, m_Name->GetPosition().y});
    m_LevelSingleDigits->SetVisible(true);
    m_LevelSingleDigits->SetZIndex(39);
    m_Root->AddChild(m_LevelSingleDigits);

    m_EXPBox = std::make_shared<Character>(RESOURCE_DIR"/UI/XPBox.png");
    m_EXPBox->SetPosition({m_LevelSingleDigits->GetPosition().x + 60, m_Name->GetPosition().y});
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
    m_EXP->SetPosition({m_LevelSingleDigits->GetPosition().x + 60, m_Name->GetPosition().y});
    m_EXP->SetVisible(true);
    m_EXP->SetLooping(false);
    m_EXP->SetZIndex(40);
    m_Root->AddChild(m_EXP);

    std::vector<std::string> CDImages;
    CDImages.reserve(10);
    for (int i = 1; i < 29; i++) {
        snprintf(buffer, sizeof(buffer), RESOURCE_DIR"/UI/CDBar/CDBar-%02d.png", i);
        CDImages.emplace_back(buffer);
    }
    m_CD = std::make_shared<AnimatedCharacter>(CDImages);
    m_CD->SetVisible(false);
    m_CD->SetLooping(false);
    m_CD->SetZIndex(40);
    m_Root->AddChild(m_CD);

    m_SelectedBlockBox = std::make_shared<Character>(RESOURCE_DIR"/UI/SelectedBlock.png");
    m_SelectedBlockBox->SetVisible(false);
    m_SelectedBlockBox->SetZIndex(39);
    m_Root->AddChild(m_SelectedBlockBox);

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
            item->SetZIndex(41);
            return true;
        }
    }

    for (int i=0; i<8; i++) {
        if (!m_InventoryItems[i]) {
            m_InventoryItems[i] = item;
            item->SetPosition(m_Inventory[i]->GetPosition());
            item->SetZIndex(41);
            if (m_Backpack->GetImageIndex() != 3) {
                item->SetVisible(false);
            }
            return true;
        }
    }
    return false;
}

void PlayerUI::DropItem() {
    if (m_DraggingItem) {
        m_DropItem = m_DraggingItem;
        // map->DropItems(Util::Input::GetCursorPosition(), m_DraggingItem);
        m_DraggingItem = nullptr;
    }
}

void PlayerUI::SwapItem(int from, int to) {
    auto& fromItem = (from < 4) ? m_ShortcutsItems[from] : m_InventoryItems[from - 4];
    auto& toItem = (to < 4) ? m_ShortcutsItems[to] : m_InventoryItems[to - 4];
    std::swap(fromItem, toItem);
}

void PlayerUI::DraggingItem() {
    if (!m_DraggingItem) {
        if (!m_Pressing && Util::Input::IsKeyDown(Util::Keycode::MOUSE_LB)) {
            for (int i = 0; i < 12; ++i) {
                if (i < 4) {
                    if (m_Shortcuts[i]->IfFocus() && m_ShortcutsItems[i]) {
                        Click_time = std::chrono::high_resolution_clock::now();
                        m_Pressing = true;
                        m_CurrentPressingIndex = i;
                        break;
                    }
                } else {
                    if (m_Inventory[i - 4]->IfFocus() && m_InventoryItems[i - 4]) {
                        Click_time = std::chrono::high_resolution_clock::now();
                        m_Pressing = true;
                        m_CurrentPressingIndex = i;
                        break;
                    }
                }
            }
        }
        if (Click_Btn == 1)
        {
            m_Pressing = false;
        }
        
        if (m_Pressing && Util::Input::IsKeyPressed(Util::Keycode::MOUSE_LB)) {
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(
                std::chrono::high_resolution_clock::now() - Click_time
            );

            if (duration.count() > 200) {
                int i = m_CurrentPressingIndex;
                if (i < 4) {
                    if (auto e = std::dynamic_pointer_cast<IEquipable>(m_ShortcutsItems[i])) {
                        e->UnEquip(player);
                    }
                    if (i == SelectedSlot)
                        SelectedSlot = -1;

                    m_DraggingItem = m_ShortcutsItems[i];
                    m_ShortcutsItems[i] = nullptr;
                } else {
                    m_DraggingItem = m_InventoryItems[i - 4];
                    m_InventoryItems[i - 4] = nullptr;
                }

                m_DraggingFromSlot = i;
                m_Pressing = false;
                m_CurrentPressingIndex = -1;
            }
        }
    }

    if (m_DraggingItem) {
        m_DraggingItem->SetPosition(Util::Input::GetCursorPosition());

        if (Util::Input::IsKeyUp(Util::Keycode::MOUSE_LB)) {
            bool dropped = false;

            for (int i = 0; i < 12; ++i) {
                bool isFocused = (i < 4) ? m_Shortcuts[i]->IfFocus() : m_Inventory[i - 4]->IfFocus();
                if (isFocused) {
                    if (i == m_DraggingFromSlot) {
                        if (m_DraggingFromSlot < 4)
                            m_ShortcutsItems[m_DraggingFromSlot] = m_DraggingItem;
                        else
                            m_InventoryItems[m_DraggingFromSlot - 4] = m_DraggingItem;

                        m_DraggingItem = nullptr;
                        dropped = true;
                        break;
                    }

                    auto& targetItem = (i < 4) ? m_ShortcutsItems[i] : m_InventoryItems[i - 4];
                    std::swap(m_DraggingItem, targetItem);

                    if (m_DraggingFromSlot < 4)
                        m_ShortcutsItems[m_DraggingFromSlot] = m_DraggingItem;
                    else
                        m_InventoryItems[m_DraggingFromSlot - 4] = m_DraggingItem;

                    m_DraggingItem = nullptr;
                    dropped = true;
                    break;
                }
            }

            if (!dropped && m_DraggingItem) {
                DropItem();
            }
            SelectedSlot = -1;
        }
    }
}


void PlayerUI::RejoinRander(Util::Renderer *m_Root){
    m_Root->AddChild(m_Name);
    m_Root->AddChild(m_HPBox);
    m_Root->AddChild(m_HP);
    m_Root->AddChild(m_MPBox);
    m_Root->AddChild(m_MP);
    m_Root->AddChild(m_EXPBox);
    m_Root->AddChild(m_EXP);
    m_Root->AddChild(m_EXPText);
    m_Root->AddChild(m_CD);
    m_Root->AddChild(m_LevelTensDigits);
    m_Root->AddChild(m_LevelSingleDigits);
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
    if (m_DraggingItem)
        m_Root->AddChild(m_DraggingItem);
}



void PlayerUI::Update(std::shared_ptr<Player> &m_Player, Util::Renderer *m_Root) {
    
    
    Click_Btn = 0;
    float deltaTime = Util::Time::GetDeltaTimeMs() / 1000.f; // 獲取每幀時間差
    deltaTime_Sum += deltaTime;
    m_SkillCD -= deltaTime; // 減少技能冷卻時間
    if (deltaTime_Sum >= 1) {
        m_Player->Restore_HP(2);
        m_Player->Restore_MP(1);
        deltaTime_Sum = 0;
    }
    
    

    if (SelectedSlot != -1) {
        m_CD->SetVisible(true);
        m_CD->SetPosition(m_Shortcuts[SelectedSlot]->GetPosition());
        int CDRate=float(m_SkillCD)/float(GetWeapon()->GetSkillCD())*28;
        if (CDRate >= 1)
            m_CD->SetCurrentFrame(CDRate-1);
        else if (CDRate <=0)
            m_CD->SetCurrentFrame(0);
        else
            m_CD->SetCurrentFrame(CDRate);
    }
    else {
        m_CD->SetVisible(false);
    }

    int HPRate=float(player->GetHP())/float(player->GetMaxHP())*100;
    if (HPRate >= 1)
        m_HP->SetCurrentFrame(HPRate-1);
    else if (HPRate >= 0)
        m_HP->SetCurrentFrame(HPRate);
    else
        m_HP->SetCurrentFrame(0);

    int MPRate=float(player->GetMP())/float(player->GetMaxMP())*100;
    if (MPRate != 0)
        m_MP->SetCurrentFrame(MPRate-1);
    else if (MPRate >= 0)
        m_MP->SetCurrentFrame(MPRate);
    else
        m_MP->SetCurrentFrame(0);

    int expRate=float(player->GetExp())/float(player->GetMaxExp())*75;
    if (expRate != 0)
        m_EXP->SetCurrentFrame(expRate-1);
    else if (expRate >= 0)
        m_EXP->SetCurrentFrame(expRate);
    else
        m_EXP->SetCurrentFrame(0);


    // 更新玩家等級顯示
    if (m_Player->GetLevel() >= 10) {
        m_LevelTensDigits->SetVisible(true);
        m_LevelTensDigits->SetImage(ExpImages[(int)(m_Player->GetLevel() / 10)]);

        m_LevelSingleDigits->SetImage(ExpImages[(int)(m_Player->GetLevel() % 10)]);
        m_LevelSingleDigits->SetPosition({m_LevelTensDigits->GetPosition().x + 20, m_Name->GetPosition().y});
        
        m_EXP->SetPosition({m_LevelSingleDigits->GetPosition().x + 60, m_Name->GetPosition().y});
        m_EXPBox->SetPosition({m_LevelSingleDigits->GetPosition().x + 60, m_Name->GetPosition().y});
    }
    else {
        m_LevelSingleDigits->SetImage(ExpImages[m_Player->GetLevel()]);
    }

    if (m_Backpack->IfClick()) {
        Click_Btn = true;
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
        Click_Btn = true;
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
        if (!m_DraggingItem && m_Inventory[i]->IfClick() && m_InventoryItems[i]) {
            Click_Btn = true;
            for (int j = 0; j < 4; j++) {
                if (!m_ShortcutsItems[j]) {
                    if (auto e = std::dynamic_pointer_cast<IEquipable>(m_InventoryItems[i])) {
                        if (SelectedSlot != -1) {
                            std::dynamic_pointer_cast<IEquipable>(m_ShortcutsItems[SelectedSlot])->UnEquip(m_Player);
                        }
                        e->Equip(m_Player);
                        m_ShortcutsItems[j] = m_InventoryItems[i];
                        m_ShortcutsItems[j]->SetPosition(m_Shortcuts[j]->GetPosition());
                        m_InventoryItems[i] = nullptr;
                        m_SkillCD = std::dynamic_pointer_cast<Weapon>(m_ShortcutsItems[j])->GetSkillCD();
                        SelectedSlot = j;
                        for (const auto& shortcut : m_Shortcuts) {
                            shortcut->ChangeImage(1);
                        }
                        m_Shortcuts[j]->ChangeImage(5);
                    }
                    break;
                }
            }
            if (auto u = std::dynamic_pointer_cast<IUsable>(m_InventoryItems[i])) {
                u->Use();
                m_Root->RemoveChild(m_InventoryItems[i]);
                m_InventoryItems[i] = nullptr;
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
        if (!m_DraggingItem && (Util::Input::IsKeyDown(keycodes[i]) || m_Shortcuts[i]->IfClick()) && m_ShortcutsItems[i]) {
            Click_Btn = true;
            if (auto e = std::dynamic_pointer_cast<IEquipable>(m_ShortcutsItems[i])) {
                if (SelectedSlot != -1) {
                    std::dynamic_pointer_cast<IEquipable>(m_ShortcutsItems[SelectedSlot])->UnEquip(m_Player);
                }
                if (SelectedSlot != i) {
                    e->Equip(m_Player);
                }
                

                if (m_Shortcuts[i]->GetImageIndex() == 2 || m_Shortcuts[i]->GetImageIndex() == 5) {
                    m_Shortcuts[i]->ChangeImage(1);
                    SelectedSlot = -1;
                }
                else {
                    // m_Shortcuts[i]->ChangeImage(5);
                    SelectedSlot = i;
                }

                for (int j = 0; j < 4; j++) {
                    if (j != i) {
                        m_Shortcuts[j]->ChangeImage(1);
                    }
                }
            }
            if (auto u = std::dynamic_pointer_cast<IUsable>(m_ShortcutsItems[i])) {
                u->Use();
                m_Root->RemoveChild(m_ShortcutsItems[i]);
                m_ShortcutsItems[i] = nullptr;
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
        if (SelectedSlot != -1) {
            m_Shortcuts[SelectedSlot]->ChangeImage(2);
            if (m_Shortcuts[SelectedSlot]->IfFocus()) {
                if (m_Shortcuts[SelectedSlot]->GetImageIndex() <= 3) {
                    m_Shortcuts[SelectedSlot]->ChangeImage(m_Shortcuts[SelectedSlot]->GetImageIndex() + 3);
                }
            }
        }
        else {
            m_Shortcuts[i]->ChangeImage(1);
        }
        if (m_Shortcuts[i]->IfFocus()) {
            if (m_Shortcuts[i]->GetImageIndex() <= 3) {
                m_Shortcuts[i]->ChangeImage(m_Shortcuts[i]->GetImageIndex() + 3);
            }
        }
    }

    for (int i = 0; i < 4; i++)
    {
        if (m_ShortcutsItems[i])
            m_ShortcutsItems[i]->SetPosition(m_Shortcuts[i]->GetPosition());
    }
    for (int i = 0; i < 8; i++)
    {
        if (m_InventoryItems[i])
            m_InventoryItems[i]->SetPosition(m_Inventory[i]->GetPosition());
    }
    
    DraggingItem();
}