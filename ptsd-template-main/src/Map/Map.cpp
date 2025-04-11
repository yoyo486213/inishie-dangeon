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
#include "Map/Box.hpp"
#include "Player.hpp"
#include "Monster/Monster.hpp"
#include "Monster/Rat.hpp"
#include "Monster/Snake.hpp"
#include "Monster/Bat.hpp"
#include "nlohmann/json.hpp"
#include <iostream>

Map::Map(Util::Renderer *m_Root) {
    std::ifstream file(RESOURCE_DIR"/Map/TiledProject/Area1_1.json");
    nlohmann::json mapData;
    file >> mapData;

    // 讀取地圖資訊
    float centerX = (mapData["width"].get<float>() * mapData["tilewidth"].get<float>()) / 2.0f;
    float centerY = (mapData["height"].get<float>() * mapData["tileheight"].get<float>()) / 2.0f;
    
    float respawnpointX = mapData["layers"][4]["objects"][0]["x"].get<float>() - centerX;
    float respawnpointY = -(mapData["layers"][4]["objects"][0]["y"].get<float>() - centerY);

    m_map = std::make_shared<Character>(RESOURCE_DIR"/Map/TiledProject/Area1_1.png");
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
        unexplored->SetZIndex(12);

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
    }

    // just push box
    m_Box = std::make_shared<Box>(RESOURCE_DIR"/Map/Chest/Box.png");
    m_Box->SetVisible(true);
    m_Box->SetZIndex(11);
    m_Box->SetPosition({-56, -28});
    m_Root->AddChild(m_Box);

    // Monster
    auto obj = std::make_shared<Rat>();
    m_Root->AddChild(obj);
    obj->SetPosition({-112, 0});
    obj->SetVisible(false);
    obj->SetZIndex(15);
    m_Monsters.push_back(std::dynamic_pointer_cast<Monster>(obj));
    AllCollidableObjects.push_back(obj);

    auto obj1 = std::make_shared<Snake>();
    m_Root->AddChild(obj1);
    obj1->SetPosition({-112, -28});
    obj1->SetVisible(true);
    obj1->SetZIndex(15);
    m_Monsters.push_back(std::dynamic_pointer_cast<Monster>(obj1));
    AllCollidableObjects.push_back(obj1);

    auto obj2 = std::make_shared<Bat>();
    m_Root->AddChild(obj2);
    obj2->SetPosition({-112, -28});
    obj2->SetVisible(false);
    obj2->SetZIndex(15);
    m_Monsters.push_back(std::dynamic_pointer_cast<Monster>(obj2));
    AllCollidableObjects.push_back(obj2);
}

void Map::Update(std::shared_ptr<Player> &m_Player) {
    if (m_CurrentInteracting) {
        m_CurrentInteracting->OnCollision();
    }

    m_UpStairs->ChangeImage(m_UpStairs->IfFouse() ? 2 : 1);
    m_DownStairs->ChangeImage(m_DownStairs->IfFouse() ? 2 : 1);

    for (const auto& monster : m_Monsters) {
        monster->Update(m_Player, AllObjects, AllCollidableObjects, m_Invisiblewalls);
    }

    m_Player->SetAttackCD(m_Player->GetAttackCD() - Util::Time::GetDeltaTimeMs() / 1000.0f);
}

void Map::Move(glm::vec2 displacement, std::shared_ptr<Player> &m_Player) {    
    // Just Push Box
    // 判斷角色推箱子時的碰撞
    bool unconti = false;
    for (const auto& item : AllCollidableObjects) {
        if (item->IsCollision(m_Box, displacement) && m_Box->IsCollision(m_Player, displacement)) {
            Move(displacement - glm::vec2(1, 1) * glm::normalize(displacement), m_Player);
            unconti = true;
        }
    }

    // main
    for (const auto& item : AllCollidableObjects) {
        if (item->IsCollision(m_Player, displacement)) {
            std::shared_ptr<Monster> monster = std::dynamic_pointer_cast<Monster>(item);
            if (monster && m_Player->GetAttackCD() <= 0) {
                monster->TakeDamage(Calculation::CalcuAttack(m_Player->GetAttack(), m_Player->GetCriticalrate()));
                m_Player->SetAttackCD(1.f);
            }
            
            m_CurrentInteracting = item;
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
    }

    //just push box
    if (m_Box->IsCollision(m_Player, displacement)) {
        return;
    }
    m_Box->SetPosition(m_Box->GetPosition() + displacement);
}