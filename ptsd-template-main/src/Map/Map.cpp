#include "Map/Map.hpp"
#include <fstream>
#include "Util/Time.hpp"
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
    

    // Monster
    std::random_device rd;
    std::mt19937 engine(rd());
    std::uniform_int_distribution<int> mapindex(4, 4);
    int index = mapindex(engine);

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
    std::uniform_int_distribution<int> monsterDist(0, 6);
    // 怪物建構工廠清單
    std::vector<std::function<std::shared_ptr<Monster>()>> monsterFactoryList = {
        []() { return std::make_shared<Rat>(); },
        []() { return std::make_shared<Snake>(); },
        []() { return std::make_shared<Worm>(); },
        []() { return std::make_shared<Slime>(); },
        []() { return std::make_shared<Zombie>(); },
        []() { return std::make_shared<Skeleton>(); },
        []() { return std::make_shared<Mage>(); }
    };
    
    // 掃地圖生成怪物
    for (int y = 0; y < 36; y++) {
        for (int x = 0; x < 36; x++) {
            if (mapData["layers"][0]["data"][y * 36 + x] == 7) {
                for (const auto& destructibleobject : m_DestructibleObjects) {
                    if (destructibleobject->GetPosition() == glm::vec2{x * 28 - centerX - respawnpointX, -(y * 28 - centerY) - respawnpointY} && chanceDist(engine) < 10) {
                        std::shared_ptr<Bat> obj = std::make_shared<Bat>();

                        m_Root->AddChild(obj);
                        m_Root->AddChild(obj->GetHPBox());
                        m_Root->AddChild(obj->GetHPBar());
                        obj->SetPosition({ x * 28 - centerX - respawnpointX, -(y * 28 - centerY) - respawnpointY});
                        obj->SetVisible(true);
                        obj->SetZIndex(15);

                        m_Monsters.push_back(obj);
                        AllCollidableObjects.push_back(obj);
                        continue;
                    }
                }
                if (occupiedTiles.count({x * 28 - centerX - respawnpointX, -(y * 28 - centerY) - respawnpointY}) > 0) {
                    continue;
                }
    
                if (chanceDist(engine) < 20) {
                    // 選一隻怪物
                    int index = monsterDist(engine);
                    auto obj = monsterFactoryList[index]();
    
                    // 加入場景
                    m_Root->AddChild(obj);
                    m_Root->AddChild(obj->GetHPBox());
                    m_Root->AddChild(obj->GetHPBar());
                    obj->SetPosition({ x * 28 - centerX - respawnpointX, -(y * 28 - centerY) - respawnpointY});
                    obj->SetVisible(true);
                    obj->SetZIndex(15);
    
                    m_Monsters.push_back(obj);
                    AllCollidableObjects.push_back(obj);
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

    if (dis(gen) < 100) {
        std::shared_ptr<Potion> potion = std::make_shared<Potion>(m_Player);
        potion->SetPosition(pos);
        potion->SetVisible(true);
        potion->SetZIndex(14);
        m_Root->AddChild(potion);
        m_Potion.push_back(potion);
        AllObjects.push_back(potion);
    }
    else if (dis(gen) < 50) {
        std::shared_ptr<Orb> orb = std::make_shared<Orb>(m_Player);
        orb->SetPosition(pos);
        orb->SetVisible(true);
        orb->SetZIndex(14);
        m_Root->AddChild(orb);
        m_Orbs.push_back(orb);
        AllObjects.push_back(orb);
    }
    else if (dis(gen) < 50) {
        std::uniform_int_distribution<int> weaponDist(0, 0);
        switch (weaponDist(gen)) {
            case 0:
                std::shared_ptr<SortSword> weapon = std::make_shared<SortSword>();
                weapon->SetPosition(pos);
                weapon->SetVisible(true);
                weapon->SetZIndex(14);
                m_Root->AddChild(weapon);
                m_Weapons.push_back(weapon);
                AllObjects.push_back(weapon);
                break;
        }
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
    

    m_UpStairs->ChangeImage(m_UpStairs->IfFouse() ? 2 : 1);
    m_DownStairs->ChangeImage(m_DownStairs->IfFouse() ? 2 : 1);
    if (m_DownStairs->IfClick() || m_UpStairs->IfClick()) {
        m_Root->ClearChildren();
        m_UI->RejoinRander(m_Root);
        m_Root->AddChild(m_Player);
        this->CreateMap(m_Root);
    }

    for (const auto& monster : m_Monsters) {
        monster->Update(m_Player, AllObjects, AllCollidableObjects, m_Invisiblewalls, m_Monsters);
        monster->UpdateHPProgress();
    }

    m_Player->SetAttackCD(m_Player->GetAttackCD() - Util::Time::GetDeltaTimeMs() / 1000.0f);
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
                    this->CreateItems(Calculation::GetRelativeCoordinates(m_UpStairs->GetPosition(), monster->GetPosition()), m_Player, m_Root);
                    monster->Restore_HP(-99999);
                }
                m_Player->SetAttackCD(1.f);
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