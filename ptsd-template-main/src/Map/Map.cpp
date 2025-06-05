#include "Map/Map.hpp"
#include "Util/Time.hpp"
#include "Util/Input.hpp"
#include "Util/Renderer.hpp"

#include "ICollidable.hpp"
#include "Calculation.hpp"
#include "Character.hpp"

#include "Map/InvisibleWall.hpp"
#include "Map/Unexplored.hpp"
#include "Map/DownStairs.hpp"
#include "Map/UpStairs.hpp"
#include "Map/Chest.hpp"
#include "Map/Door.hpp"
#include "Map/DestructibleObject.hpp"

#include "Items/Item.hpp"
#include "Items/Potion.hpp"
#include "Items/Orb.hpp"

#include "Weapon/Weapon.hpp"
#include "Weapon/SortSword.hpp"
#include "Weapon/Bow.hpp"
#include "Weapon/HunterBow.hpp"
#include "Weapon/Buckler.hpp"
#include "Weapon/FireRod.hpp"
#include "Weapon/IceRod.hpp"
#include "Weapon/Club.hpp"
#include "Weapon/Dagger.hpp"
#include "Weapon/HandAx.hpp"
#include "Weapon/Dark.hpp"
#include "Weapon/Mace.hpp"

#include "Player.hpp"
#include "Menus/PlayerUI.hpp"

#include "Monster/Monster.hpp"
#include "Monster/Rat.hpp"
#include "Monster/Snake.hpp"
#include "Monster/Bat.hpp"
#include "Monster/Worm.hpp"
#include "Monster/Slime.hpp"
#include "Monster/Zombie.hpp"
#include "Monster/Skeleton.hpp"
#include "Monster/Mage.hpp"

#include "nlohmann/json.hpp"
#include <iostream>
#include <fstream>
#include <memory>
#include <set>

Map::Map(Util::Renderer *m_Root) {
    CreateMap(m_Root);
}

void Map::CreateMap(Util::Renderer *m_Root) {
    //init
    // 清空單一物件
    m_map = nullptr;
    m_UpStairs = nullptr;
    m_DownStairs = nullptr;
    m_CurrentInteracting = nullptr;
    // 清空容器類物件
    m_DestructibleObjects.clear();
    m_Doors.clear();
    m_Chests.clear();
    m_Unexploreds.clear();
    m_Invisiblewalls.clear();
    m_Potion.clear();
    m_Orbs.clear();
    AllCollidableObjects.clear();
    AllObjects.clear();
    m_Monsters.clear();

    m_FloorText = std::make_shared<Text>(FloorImages[0]);
    m_FloorText->SetZIndex(60);
    m_FloorText->SetPosition({250, 206});
    m_FloorText->SetVisible(true);
    m_Root->AddChild(m_FloorText);

    m_FloorTensDigits = std::make_shared<Text>(FloorImages[(int)(floor / 10)]);
    m_FloorTensDigits->SetZIndex(60);
    m_FloorTensDigits->SetPosition(m_FloorText->GetPosition() + glm::vec2(30, 0));
    m_FloorTensDigits->SetVisible(false);
    m_Root->AddChild(m_FloorTensDigits);

    m_FloorSingleDigits = std::make_shared<Text>(FloorImages[floor % 10]);
    m_FloorSingleDigits->SetZIndex(60);
    (floor >= 10) ? m_FloorSingleDigits->SetPosition(m_FloorTensDigits->GetPosition() + glm::vec2(30, 0)) : m_FloorSingleDigits->SetPosition(m_FloorText->GetPosition() + glm::vec2(30, 0));
    m_FloorSingleDigits->SetVisible(true);
    m_Root->AddChild(m_FloorSingleDigits);

    // Monster
    std::random_device rd;
    std::mt19937 engine(rd());
    std::uniform_int_distribution<int> mapindex(1, 9);
    int index = mapindex(engine);
    while (index == beforemapindex) {
        index = mapindex(engine);
    }
    beforemapindex = index;

    std::ifstream file(std::string(RESOURCE_DIR) + "/Map/TiledProject/Area1_" + std::to_string(index) + ".json");
    nlohmann::json mapData;
    file >> mapData;

    std::set<std::pair<int, int>> occupiedTiles;  // 儲存已被佔用的 tile 座標

    // 讀取地圖資訊
    float centerX = (mapData["width"].get<float>() * mapData["tilewidth"].get<float>()) / 2.0f;
    float centerY = (mapData["height"].get<float>() * mapData["tileheight"].get<float>()) / 2.0f;
    
    float respawnpointX = mapData["layers"][4]["objects"][0]["x"].get<float>() - centerX;
    float respawnpointY = -(mapData["layers"][4]["objects"][0]["y"].get<float>() - centerY);

    m_map = std::make_shared<Character>(std::string(RESOURCE_DIR) + "/Map/TiledProject/Area1_" + std::to_string(index) + ".png");
    m_map->SetZIndex(10);
    m_map->SetPosition({-respawnpointX - 14, -respawnpointY + 14});
    m_map->SetVisible(true);
    AllObjects.push_back(m_map);
    m_Root->AddChild(m_map);

    for (const auto& object : mapData["layers"][2]["objects"]) {
        float newX = object["x"].get<float>() - centerX;
        float newY = -(object["y"].get<float>() - centerY);

        // 創建物件並設置屬性
        auto unexplored = std::make_shared<Unexplored>(RESOURCE_DIR"/Map/TiledProject/Area1_Resources/" + object["name"].get<std::string>() + ".png");
        AllObjects.push_back(unexplored);

        unexplored->SetPosition({newX - respawnpointX, newY - respawnpointY + 28});
        unexplored->SetVisible(true);
        unexplored->SetZIndex(16);

        m_Root->AddChild(unexplored);
        m_Unexploreds.push_back(unexplored);
    }

    for (const auto& object : mapData["layers"][3]["objects"]) {
        float newX = object["x"].get<float>() - centerX;
        float newY = -(object["y"].get<float>() - centerY);

        // 創建物件並設置屬性
        auto invisiblewall = std::make_shared<InvisibleWall>(glm::vec2(object["width"].get<float>(), object["height"].get<float>()));
        AllCollidableObjects.push_back(invisiblewall);
        
        invisiblewall->SetPosition({newX - respawnpointX + object["width"].get<float>() / 2.0 - 14, newY - respawnpointY - object["height"].get<float>() / 2.0 + 14});
        m_Invisiblewalls.push_back(invisiblewall);
        occupiedTiles.insert({static_cast<int>(newX - respawnpointX + object["width"].get<float>() / 2.0 - 14), static_cast<int>(newY - respawnpointY - object["height"].get<float>() / 2.0 + 14)}); // 儲存 tile 座標
    }

    // 遍歷所有物件並調整位置
    for (const auto& object : mapData["layers"][1]["objects"]) {
        float newX = object["x"].get<float>() - centerX;
        float newY = -(object["y"].get<float>() - centerY);

        // 創建物件並設置屬性
        std::shared_ptr<Character> obj;
        if (object["name"].get<std::string>() == "Door") {
            obj = std::make_shared<Door>(RESOURCE_DIR"/Map/TiledProject/Area1_Resources/" + object["name"].get<std::string>() + ".png", m_Unexploreds);
            m_Doors.push_back(std::dynamic_pointer_cast<Door>(obj));
            AllObjects.push_back(std::dynamic_pointer_cast<Door>(obj));
            AllCollidableObjects.push_back(std::dynamic_pointer_cast<Door>(obj));
        }
        else if (object["name"].get<std::string>() == "CloseChest") {
            obj = std::make_shared<Chest>(RESOURCE_DIR"/Map/TiledProject/Area1_Resources/" + object["name"].get<std::string>() + ".png", m_Root);
            m_Chests.push_back(std::dynamic_pointer_cast<Chest>(obj));
            AllObjects.push_back(std::dynamic_pointer_cast<Chest>(obj));
            AllCollidableObjects.push_back(std::dynamic_pointer_cast<Chest>(obj));
        }
        else if (object["name"].get<std::string>() == "UpStairs") {
            obj = std::make_shared<UpStairs>(RESOURCE_DIR"/Map/TiledProject/Area1_Resources/" + object["name"].get<std::string>() + ".png", m_Root);
            m_UpStairs = std::dynamic_pointer_cast<UpStairs>(obj);
            AllObjects.push_back(std::dynamic_pointer_cast<UpStairs>(obj));
        }
        else if (object["name"].get<std::string>() == "DownStairs") {
            obj = std::make_shared<DownStairs>(RESOURCE_DIR"/Map/TiledProject/Area1_Resources/" + object["name"].get<std::string>() + ".png", m_Root);
            m_DownStairs = std::dynamic_pointer_cast<DownStairs>(obj);
            AllObjects.push_back(std::dynamic_pointer_cast<DownStairs>(obj));
        }
        else {
            obj = std::make_shared<DestructibleObject>(RESOURCE_DIR"/Map/TiledProject/Area1_Resources/" + object["name"].get<std::string>() + ".png");
            m_DestructibleObjects.push_back(std::dynamic_pointer_cast<DestructibleObject>(obj));
            AllObjects.push_back(std::dynamic_pointer_cast<DestructibleObject>(obj));
            AllCollidableObjects.push_back(std::dynamic_pointer_cast<DestructibleObject>(obj));
        }

        obj->SetPosition({newX - respawnpointX, newY - respawnpointY + 28});
        obj->SetVisible(true);
        obj->SetZIndex(11);

        m_Root->AddChild(obj);
        occupiedTiles.insert({static_cast<int>(newX - respawnpointX), static_cast<int>(newY - respawnpointY + 28)}); // 儲存 tile 座標
    }

    std::uniform_int_distribution<int> chanceDist(0, 99);

    // 怪物建構工廠清單（依 floor 動態選）
    auto getMonsterFactoryList = [&](int floor) {
        std::vector<std::function<std::shared_ptr<Monster>()>> list;

        if (floor >= 1) {
            list.push_back([]() { return std::make_shared<Rat>(); });
            list.push_back([]() { return std::make_shared<Snake>(); });
            list.push_back([]() { return std::make_shared<Bat>(); });
            list.push_back([]() { return std::make_shared<Worm>(); });
        }
        if (floor >= 4) {
            list.push_back([]() { return std::make_shared<Slime>(); });
        }
        if (floor >= 6) {
            list.push_back([]() { return std::make_shared<Skeleton>(); });
            list.push_back([]() { return std::make_shared<Mage>(); });
        }
        if (floor >= 8) {
            list.push_back([]() { return std::make_shared<Zombie>(); });
        }

        return list;
    };

    // 掃地圖生成怪物
    for (int y = 0; y < 36; y++) {
        for (int x = 0; x < 36; x++) {
            if (mapData["layers"][0]["data"][y * 36 + x] == 7) {
                glm::vec2 pos = { x * 28 - centerX - respawnpointX, -(y * 28 - centerY) - respawnpointY };

                for (const auto& destructibleobject : m_DestructibleObjects) {
                    if (destructibleobject->GetPosition() == pos && chanceDist(engine) < 10) {
                        std::shared_ptr<Bat> obj = std::make_shared<Bat>();

                        m_Root->AddChild(obj);
                        m_Root->AddChild(obj->GetHPBox());
                        m_Root->AddChild(obj->GetHPBar());
                        obj->SetPosition(pos);
                        obj->SetVisible(true);
                        obj->SetZIndex(15);

                        m_Monsters.push_back(obj);
                        AllCollidableObjects.push_back(obj);
                        continue;
                    }
                }

                std::pair<int, int> tilePos = { static_cast<int>(pos.x), static_cast<int>(pos.y) };
                if (occupiedTiles.count(tilePos) > 0) {
                    continue;
                }

                // 第 10 層為 BOSS 房間
                if (floor == 10) {
                    // if (mapData["layers"][1]["data"][y * 36 + x] == BOSS_SPAWN_TILE) {
                    //     auto boss = std::make_shared<Boss>();
                    //     m_Root->AddChild(boss);
                    //     m_Root->AddChild(boss->GetHPBox());
                    //     m_Root->AddChild(boss->GetHPBar());
                    //     boss->SetPosition(pos);
                    //     boss->SetVisible(true);
                    //     boss->SetZIndex(15);
                    //     m_Monsters.push_back(boss);
                    //     AllCollidableObjects.push_back(boss);
                    // } else if (chanceDist(engine) < 20) {
                    //     auto rat = std::make_shared<Rat>();
                    //     m_Root->AddChild(rat);
                    //     m_Root->AddChild(rat->GetHPBox());
                    //     m_Root->AddChild(rat->GetHPBar());
                    //     rat->SetPosition(pos);
                    //     rat->SetVisible(true);
                    //     rat->SetZIndex(15);
                    //     m_Monsters.push_back(rat);
                    //     AllCollidableObjects.push_back(rat);
                    // }
                } else {
                    // 一般樓層怪物生成
                    auto monsterList = getMonsterFactoryList(floor);
                    if (!monsterList.empty() && chanceDist(engine) < 10) {
                        std::uniform_int_distribution<int> monsterDist(0, monsterList.size() - 1);
                        auto obj = monsterList[monsterDist(engine)]();

                        m_Root->AddChild(obj);
                        m_Root->AddChild(obj->GetHPBox());
                        m_Root->AddChild(obj->GetHPBar());
                        obj->SetPosition(pos);
                        obj->SetVisible(true);
                        obj->SetZIndex(15);

                        m_Monsters.push_back(obj);
                        AllCollidableObjects.push_back(obj);
                    }
                }
            }
        }
    }

    for (const auto& monster : m_Monsters) {
        monster->SetGoalPosition(monster->GetPosition());
    }
}

void Map::CreateItems(glm::vec2 pos, std::shared_ptr<Player> &m_Player, Util::Renderer *m_Root) {
    // 這邊是用來創建物品的
    // 目前是隨機生成
    std::random_device rd;
    std::mt19937 gen(rd()); // 以隨機設備為種子初始化 Mersenne Twister 引擎
    std::uniform_int_distribution<> dis(1, 100); // 設置範圍 (最小值到最大值)

    for (const auto& potion : m_Potion) {
        if (potion->GetPosition() == pos) {
            return;
        }
    }
    for (const auto& orb : m_Orbs) {
        if (orb->GetPosition() == pos) {
            return;
        }
    }
    for (const auto& weapon : m_Weapons) {
        if (weapon->GetPosition() == pos) {
            return;
        }
    }

    if (dis(gen) < 0) {
        std::shared_ptr<Potion> potion = std::make_shared<Potion>(m_Player);
        potion->SetPosition(pos);
        potion->SetVisible(true);
        potion->SetZIndex(14);
        m_Root->AddChild(potion);
        m_Potion.push_back(potion);
        AllObjects.push_back(potion);
    }
    else if (dis(gen) < 0) {
        std::shared_ptr<Orb> orb = std::make_shared<Orb>(m_Player);
        orb->SetPosition(pos);
        orb->SetVisible(true);
        orb->SetZIndex(14);
        m_Root->AddChild(orb);
        m_Orbs.push_back(orb);
        AllObjects.push_back(orb);
    }
    else if (dis(gen) < 100) {
        std::uniform_int_distribution<int> weaponDist(10, 10);
        std::shared_ptr<Weapon> weapon;

        switch (weaponDist(gen)) {
            case 0:
                weapon = std::make_shared<SortSword>();
                break;
            case 1:
                weapon = std::make_shared<Bow>();
                break;
            case 2:
                weapon = std::make_shared<HunterBow>();
                break;
            case 3:
                weapon = std::make_shared<Buckler>();
                break;
            case 4:
                weapon = std::make_shared<FireRod>();
                break;
            case 5:
                weapon = std::make_shared<IceRod>();
                break;
            case 6:
                weapon = std::make_shared<Club>();
                break;
            case 7:
                weapon = std::make_shared<Dagger>();
                break;
            case 8:
                weapon = std::make_shared<HandAx>();
                break;
            case 9:
                weapon = std::make_shared<Dark>();
                break;
            case 10:
                weapon = std::make_shared<Mace>();
                break;
        }

        weapon->SetPosition(pos);
        weapon->SetVisible(true);
        weapon->SetZIndex(14);
        m_Root->AddChild(weapon);
        m_Weapons.push_back(weapon);
        AllObjects.push_back(weapon);
    }
}

void Map::Update(std::shared_ptr<Player> &m_Player, std::shared_ptr<PlayerUI> &m_UI, Util::Renderer *m_Root) {
    if (m_CurrentInteracting) {
        m_CurrentInteracting->OnCollision();

        auto chest = std::dynamic_pointer_cast<Chest>(m_CurrentInteracting);
        if (chest && chest->GetOpened() == Chest::OpenType::Normal) {
            chest->SetOpened(Chest::OpenType::Trash);
            const std::vector<glm::vec2> directions = {
                {0, 1}, {0, -1}, {-1, 0}, {1, 0}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}
            };
            for (const auto& dir : directions) {
                this->CreateItems(chest->GetPosition() + dir * 28.f, m_Player, m_Root);
            }
        }
    }
    // 判斷是否點擊放進快捷欄
    for (auto it = m_Potion.begin(); it != m_Potion.end(); ) {
        auto& potion = *it;
        if (potion->IfClick()) {
            if (m_UI->PeekItem(std::dynamic_pointer_cast<Item>(potion))) {
                AllObjects.erase(std::remove(AllObjects.begin(), AllObjects.end(), potion), AllObjects.end());
                it = m_Potion.erase(it);
                continue;
            }
        }
    
        /*
        if (potion->IfFocus()) {
            // 給他背景
        } else {
            // 取消背景
        }
        */
    
        ++it;
    }
    for (auto it = m_Weapons.begin(); it != m_Weapons.end(); ) {
        auto& weapon = *it;
        if (weapon->IfClick()) {
            if (m_UI->PeekItem(std::dynamic_pointer_cast<Item>(weapon))) {
                AllObjects.erase(std::remove(AllObjects.begin(), AllObjects.end(), weapon), AllObjects.end());
                it = m_Weapons.erase(it);
                continue;
            }
        }
    
        /*
        if (potion->IfFocus()) {
            // 給他背景
        } else {
            // 取消背景
        }
        */
    
        ++it;
    }
    

    m_UpStairs->ChangeImage(m_UpStairs->IfFouse() ? 2 : 1);
    m_DownStairs->ChangeImage(m_DownStairs->IfFouse() ? 2 : 1);
    if (m_DownStairs->IfClick()) {
        m_Root->ClearChildren();
        floor += 1;
        m_UI->RejoinRander(m_Root);
        m_Root->AddChild(m_Player);
        this->CreateMap(m_Root);
    }
    else if (m_UpStairs->IfClick()) {
        m_Root->ClearChildren();
        if (floor > 1) {
            floor -= 1;
        }
        m_UI->RejoinRander(m_Root);
        m_Root->AddChild(m_Player);
        this->CreateMap(m_Root);
    }

    for (const auto& monster : m_Monsters) {
        monster->Update(m_Player, AllObjects, AllCollidableObjects, m_Invisiblewalls, m_Monsters);
        monster->UpdateHPProgress();
    }

    m_Player->SetAttackCD(m_Player->GetAttackCD() - Util::Time::GetDeltaTimeMs() / 1000.0f);

    // 實作武器技能
    if (Util::Input::IsKeyDown(Util::Keycode::MOUSE_LB) && m_UI->IsEquip() && !std::dynamic_pointer_cast<Buckler>(m_UI->GetWeapon())) {
        auto bow = std::dynamic_pointer_cast<Bow>(m_UI->GetWeapon());
        auto hunterBow = std::dynamic_pointer_cast<HunterBow>(m_UI->GetWeapon());
        if (m_UI->GetSkillCD() <= 0 && m_Player->GetMP() - m_UI->GetWeapon()->GetSkillCost() >= 0) {
            m_UI->SetSkillCD(m_UI->GetWeapon()->GetSkillCD());
            m_Player->Restore_MP(-m_UI->GetWeapon()->GetSkillCost());
            m_UI->GetWeapon()->Skill(shared_from_this(), m_Player, m_Root);
        }
        else if (bow && m_Player->GetAttackCD() <= 0) {
            m_Player->SetAttackCD(m_Player->GetDefaultAttackCD());
            bow->Attack(shared_from_this(), m_Player, m_Root);
        }
        else if (hunterBow && m_Player->GetAttackCD() <= 0) {
            m_Player->SetAttackCD(m_Player->GetDefaultAttackCD());
            hunterBow->Attack(shared_from_this(), m_Player, m_Root);
        }
    }
    
    // 判斷武器碰撞
    for (auto it = m_Projectiles.begin(); it != m_Projectiles.end(); ) {
        auto& projectile = *it;
        projectile->Update(m_Player);

        if (!projectile->CanCollide()) { 
            ++it;
            continue; 
        }

        bool shouldErase = false;

        for (const auto& object : AllCollidableObjects) {
            if (object->IsCollision(projectile, glm::vec2(0, 0))) {
                if (projectile->GetSkillRange() > 0) {
                    for (const auto& object2 : AllCollidableObjects) {
                        std::shared_ptr<Monster> monster = std::dynamic_pointer_cast<Monster>(object2);
                        if (monster && glm::distance(projectile->GetPosition(), monster->GetPosition()) <= projectile->GetSkillRange() * 28) {
                            monster->TakeDamage(Calculation::CalcuAttack(projectile->GetDamage(), m_Player->GetCriticalrate()));
                            if (monster->GetHP() >= -10000 && monster->GetHP() <= 0) {
                                m_Player->Restore_EXP(monster->GetExp());
                                this->CreateItems(Calculation::GetRelativeCoordinates(m_UpStairs->GetPosition(), monster->GetPosition()), m_Player, m_Root);
                                monster->Restore_HP(-99999);
                                monster->SetHPVisible(false);
                                m_Monsters.erase(std::remove(m_Monsters.begin(), m_Monsters.end(), monster), m_Monsters.end());
                            }
                        }
                    }
                } else {
                    std::shared_ptr<Monster> monster = std::dynamic_pointer_cast<Monster>(object);
                    if (monster) {
                        monster->TakeDamage(Calculation::CalcuAttack(projectile->GetDamage(), m_Player->GetCriticalrate()));
                        if (monster->GetHP() >= -10000 && monster->GetHP() <= 0) {
                            m_Player->Restore_EXP(monster->GetExp());
                            this->CreateItems(Calculation::GetRelativeCoordinates(m_UpStairs->GetPosition(), monster->GetPosition()), m_Player, m_Root);
                            monster->Restore_HP(-99999);
                            monster->SetHPVisible(false);
                            m_Monsters.erase(std::remove(m_Monsters.begin(), m_Monsters.end(), monster), m_Monsters.end());
                        }
                    }
                }

                // 標記這個 projectile 應該被移除
                if (projectile->ShouldDisappear()) {
                    shouldErase = true;
                }
                else {
                    projectile->SetSpeed(0);
                    projectile->SetState(State::Staying);
                }
                break;  // 避免同一個 projectile 重複碰撞
            }
        }

        if (shouldErase) {
            // 從 m_Root 移除
            m_Root->RemoveChild(projectile);
            // 從 m_Projectiles 移除
            it = m_Projectiles.erase(it);
        } else {
            ++it;
        }
    }
}

void Map::Move(glm::vec2 displacement, std::shared_ptr<Player> &m_Player, Util::Renderer *m_Root) {    
    bool unconti = false;
    // main
    for (const auto& item : AllCollidableObjects) {
        if (item->IsCollision(m_Player, displacement)) {
            std::shared_ptr<Monster> monster = std::dynamic_pointer_cast<Monster>(item);
            if (monster && m_Player->GetAttackCD() <= 0) {
                monster->TakeDamage(Calculation::CalcuAttack(m_Player->GetAttack(), m_Player->GetCriticalrate()));
                if (monster->GetHP() >= -10000 && monster->GetHP() <= 0) {
                    m_Player->Restore_EXP(monster->GetExp());

                    this->CreateItems(Calculation::GetRelativeCoordinates(m_UpStairs->GetPosition(), monster->GetPosition()), m_Player, m_Root);
                    monster->Restore_HP(-99999);
                    monster->SetHPVisible(false);
                    m_Monsters.erase(std::remove(m_Monsters.begin(), m_Monsters.end(), monster), m_Monsters.end());
                }
                m_Player->SetAttackCD(m_Player->GetDefaultAttackCD());
            }
            
            m_CurrentInteracting = item;
            unconti = true;
        }
    }
    for (const auto& orb : m_Orbs) {
        if (orb->IsCollision(m_Player, displacement)) {
            orb->OnCollision(m_Player);
            orb->SetVisible(false);
            unconti = true;
        }
    }
    m_UpStairs->IsCollision(m_Player, displacement) ? m_UpStairs->OnCollision() : m_UpStairs->OffCollision();
    m_DownStairs->IsCollision(m_Player, displacement) ? m_DownStairs->OnCollision() : m_DownStairs->OffCollision();
    if (unconti) {
        return;
    }

    if (m_CurrentInteracting) {
        m_CurrentInteracting->OffCollision();
        m_CurrentInteracting = nullptr;
    }
    for (const auto& item : AllObjects) {
        item->SetPosition(item->GetPosition() + displacement);
    }
    for (const auto& invisiblewall : m_Invisiblewalls) {
        invisiblewall->SetPosition(invisiblewall->GetPosition() + displacement);
    }
    for (const auto& monster : m_Monsters) {
        monster->SetPosition(monster->GetPosition() + displacement);
        monster->SetPosPosition(monster->GetPosPosition() + displacement);
        monster->SetGoalPosition(monster->GetGoalPosition() + displacement);
    }
}