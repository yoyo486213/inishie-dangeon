#include "Menus/PlayerUI.hpp"
#include "Player.hpp"
#include "Util/Renderer.hpp"
#include "AnimatedCharacter.hpp"

PlayerUI::PlayerUI(std::shared_ptr<Player> playerRef, Util::Renderer *m_Root) : player(playerRef) {
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
    m_HP->SetCurrentFrame(99);
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
    m_MP->SetCurrentFrame(99);
    m_MP->SetVisible(true);
    m_MP->SetLooping(false);
    m_MP->SetZIndex(40);
    m_Root->AddChild(m_MP);


    m_EXPBox = std::make_shared<Character>(RESOURCE_DIR"/UI/MPBox.png");
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



    std::vector<std::string> ShortcutsImages;  
    ShortcutsImages.reserve(3);
    for (int i = 1; i < 4; i++) {
        snprintf(buffer, sizeof(buffer), RESOURCE_DIR"/UI/XPBar/XPBar-%02d.png", i);
        ShortcutsImages.emplace_back(buffer);
    }
    for (int i = 0; i < 4; i++) {
        m_Shortcuts.emplace_back(std::make_shared<AnimatedCharacter>(ShortcutsImages));
        m_Shortcuts[i]->SetZIndex(40);
        m_Shortcuts[i]->SetPosition({50 + 30*i, -300});
        m_Shortcuts[i]->SetVisible(true);
        m_Root->AddChild(m_Shortcuts[i]);
    }

    std::vector<std::string> InventoryImages;  
    InventoryImages.reserve(3);
    for (int i = 1; i < 4; i++) {
        snprintf(buffer, sizeof(buffer), RESOURCE_DIR"/UI/XPBar/XPBar-%02d.png", i);
        InventoryImages.emplace_back(buffer);
    }
    for (int i = 0; i < 4; i++) {
        m_Inventory.emplace_back(std::make_shared<AnimatedCharacter>(InventoryImages));
        m_Inventory[i]->SetZIndex(40);
        m_Inventory[i]->SetPosition({50 + 30*i, -300});
        m_Inventory[i]->SetVisible(true);
        m_Root->AddChild(m_Inventory[i]);
    }
}


void PlayerUI::Update() {
    int HPRate=float(player->GetHP())/float(player->GetMaxHP())*100;
    if (HPRate != 0)
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
    else
        m_EXP->SetCurrentFrame(expRate);
}