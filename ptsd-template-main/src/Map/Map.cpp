#include "Map/Map.hpp"

Map::Map(Util::Renderer *m_Root) {
    std::ifstream file("../Resources/Map/TiledProject/Area1_2.json");
    nlohmann::json mapData;
    file >> mapData;

    // 讀取地圖資訊
    float centerX = (mapData["width"].get<float>() * mapData["tilewidth"].get<float>()) / 2.0f;
    float centerY = (mapData["height"].get<float>() * mapData["tileheight"].get<float>()) / 2.0f;
    
    float respawnpointX = mapData["layers"][4]["objects"][0]["x"].get<float>() - centerX;
    float respawnpointY = -(mapData["layers"][4]["objects"][0]["y"].get<float>() - centerY);

    m_map = std::make_shared<Character>("../Resources/Map/TiledProject/Area1_2.png");
    m_map->SetZIndex(10);
    m_map->SetPosition({-respawnpointX - 14, -respawnpointY + 14});
    m_map->SetVisible(true);
    m_Root->AddChild(m_map);

    // 遍歷所有物件並調整位置
    for (const auto& object : mapData["layers"][1]["objects"]) {
        float newX = object["x"].get<float>() - centerX;
        float newY = -(object["y"].get<float>() - centerY);

        // 創建物件並設置屬性
        auto obj = std::make_shared<Character>("../Resources/Map/TiledProject/Area1_Resources/" + object["name"].get<std::string>() + ".png");
        
        obj->SetPosition({newX - respawnpointX, newY - respawnpointY + 28});
        obj->SetVisible(true);
        obj->SetZIndex(11);

        m_Root->AddChild(obj);
        m_Objects.push_back(obj);
    }

    // for (const auto& object : mapData["layers"][2]["objects"]) {
    //     float newX = object["x"].get<float>() - centerX;
    //     float newY = object["y"].get<float>() - centerY;

    //     // 創建物件並設置屬性
    //     auto obj = std::make_shared<Character>("../Resources/Map/TiledProject/Area1_Resources/" + object["name"].get<std::string>() + ".png");
        
    //     obj->SetPosition({newX - respawnpointX, -newY + respawnpointY});
    //     obj->SetVisible(true);
    //     obj->SetZIndex(11);

    //     m_Root->AddChild(obj);
    //     m_Objects.push_back(obj);
    // }

    for (const auto& object : mapData["layers"][3]["objects"]) {
        float newX = object["x"].get<float>() - centerX;
        float newY = -(object["y"].get<float>() - centerY);

        // 創建物件並設置屬性
        auto invisiblewall = std::make_shared<InvisibleWall>(glm::vec2(object["width"].get<float>(), object["height"].get<float>()));
        
        invisiblewall->SetPosition({newX - respawnpointX - 14, newY - respawnpointY + 14});
        m_Invisiblewalls.push_back(invisiblewall);
    }
}

void Map::Update() {
    // for (const auto& invisiblewall : m_Invisiblewalls) {
    //     if (invisiblewall->IsCollision()) {
    //         m_map->SetPosition({m_map->GetPosition().x + displacement.x, m_map->GetPosition().y + displacement.y});
    //         for (const auto& obj : m_Objects) {
    //             obj->SetPosition({obj->GetPosition().x + displacement.x, obj->GetPosition().y + displacement.y});
    //         }
    //         for (const auto& invisiblewall : m_Invisiblewalls) {
    //             invisiblewall->SetPosition({invisiblewall->GetPosition().x + displacement.x, invisiblewall->GetPosition().y + displacement.y});
    //         }
    //     }
    // }
}

void Map::Move(glm::vec2 displacement) { 
    for (const auto& invisiblewall : m_Invisiblewalls) {
        if (invisiblewall->IsCollision({invisiblewall->GetPosition().x + displacement.x, invisiblewall->GetPosition().y + displacement.y})) {
            return;
        }
    }

    m_map->SetPosition({m_map->GetPosition().x + displacement.x, m_map->GetPosition().y + displacement.y});
    for (const auto& obj : m_Objects) {
        obj->SetPosition({obj->GetPosition().x + displacement.x, obj->GetPosition().y + displacement.y});
    }
    for (const auto& invisiblewall : m_Invisiblewalls) {
        invisiblewall->SetPosition({invisiblewall->GetPosition().x + displacement.x, invisiblewall->GetPosition().y + displacement.y});
    }
}