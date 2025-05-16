#include "Menus/PlayerUI.hpp"
#include "Util/Renderer.hpp"
#include "Util/Input.hpp"
#include "AnimatedCharacter.hpp"
#include "Text.hpp"
#include "Player.hpp"
#include "Items/Item.hpp"
#include "Items/Potion.hpp"

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

    m_EXPBox = std::make_shared<Character>(RESOURCE_DIR"/UI/XPBox.png");
    m_EXPBox->SetPosition({-110 , 208});
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
}


void PlayerUI::Update() {
    m_Name->SetPosition({-230+m_Name->GetScaledSize().x/2 ,223+m_Name->GetScaledSize().y/2});

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

    if (Util::Input::IsKeyDown(Util::Keycode::NUM_1) && m_ShortcutsItems[0]) {
        m_ShortcutsItems[0]->Use();
        m_ShortcutsItems[0] = nullptr;
    }
    else if (Util::Input::IsKeyDown(Util::Keycode::NUM_2) && m_ShortcutsItems[1]) {
        m_ShortcutsItems[1]->Use();
        m_ShortcutsItems[1] = nullptr;
    }
    else if (Util::Input::IsKeyDown(Util::Keycode::NUM_3) && m_ShortcutsItems[2]) {
        m_ShortcutsItems[2]->Use();
        m_ShortcutsItems[2] = nullptr;
    }
    else if (Util::Input::IsKeyDown(Util::Keycode::NUM_4) && m_ShortcutsItems[3]) {
        m_ShortcutsItems[3]->Use();
        m_ShortcutsItems[3] = nullptr;
    }
}

bool PlayerUI::PeekItem(std::shared_ptr<Item> item) {
    for (int i=0; i<4; i++) {
        if (!m_ShortcutsItems[i]) {
            m_ShortcutsItems[i] = item;
            return true;
        }
    }

    for (int i=0; i<8; i++) {
        if (!m_InventoryItems[i]) {
            m_InventoryItems[i] = item;
            return true;
        }
    }

    return false;
}