#ifndef MAP_HPP
#define MAP_HPP

#include "InvisibleWall.hpp"
#include "pch.hpp"
#include <fstream> 
#include <iostream>
#include "Util/GameObject.hpp"
#include "Util/Renderer.hpp"
#include "Character.hpp"
#include "Map/InvisibleWall.hpp"
#include "nlohmann/json.hpp"

class Map : public Util::GameObject {
public:
    Map(Util::Renderer *m_Root) {
        m_map = std::make_shared<Character>("../Resources/Map/TiledProject/Area1_1.png");
        m_map->SetZIndex(10);
        m_map->SetPosition({0, 0});
        m_map->SetVisible(true);
        m_Root->AddChild(m_map);

        std::ifstream file("../Resources/Map/TiledProject/Area1_1.json");
        nlohmann::json mapData;
        file >> mapData;

       // 讀取地圖資訊
       float centerX = (mapData["width"].get<float>() * mapData["tilewidth"].get<float>()) / 2.0f;
       float centerY = (mapData["height"].get<float>() * mapData["tileheight"].get<float>()) / 2.0f;

        // 遍歷所有物件並調整位置
        for (const auto& object : mapData["layers"][1]["objects"]) {
            float newX = object["x"].get<float>() - centerX + object.value("width", 0.0f) / 2.0f;
            float newY = object["y"].get<float>() - centerY - object.value("height", 0.0f) / 2.0f;

            // 創建物件並設置屬性
            auto obj = std::make_shared<Character>("../Resources/Map/TiledProject/Area1_Resources/" + object["name"].get<std::string>() + ".png");
            
            obj->SetPosition({newX, -newY});
            obj->SetVisible(true);
            obj->SetZIndex(15);

            m_Root->AddChild(obj);
            m_Objects.push_back(obj);
        }
    }

    void Move(glm::vec2 displacement) {
        m_map->SetPosition({m_map->GetPosition().x + displacement.x, m_map->GetPosition().y + displacement.y});
        for (auto& obj : m_Objects) {
            obj->SetPosition({obj->GetPosition().x + displacement.x, obj->GetPosition().y + displacement.y});
        }
    }
private:
    std::shared_ptr<Character> m_map;
    std::vector<std::shared_ptr<Character>> m_Objects;
    std::vector<std::shared_ptr<InvisibleWall>> m_Invisiblewall;
};

#endif //MAP_HPP