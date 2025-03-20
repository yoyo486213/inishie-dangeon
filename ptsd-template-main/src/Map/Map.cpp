#include "Map/Map.hpp"
#include <memory>

Map::Map(Util::Renderer *m_Root) {
    std::ifstream file("../Resources/Map/TiledProject/Area1_1.json");
    nlohmann::json mapData;
    file >> mapData;

    // 讀取地圖資訊
    float centerX = (mapData["width"].get<float>() * mapData["tilewidth"].get<float>()) / 2.0f;
    float centerY = (mapData["height"].get<float>() * mapData["tileheight"].get<float>()) / 2.0f;
    
    float respawnpointX = mapData["layers"][4]["objects"][0]["x"].get<float>() - centerX;
    float respawnpointY = -(mapData["layers"][4]["objects"][0]["y"].get<float>() - centerY);

    m_map = std::make_shared<Character>("../Resources/Map/TiledProject/Area1_1.png");
    m_map->SetZIndex(10);
    m_map->SetPosition({-respawnpointX - 14, -respawnpointY + 14});
    m_map->SetVisible(true);
    m_Root->AddChild(m_map);

    for (const auto& object : mapData["layers"][2]["objects"]) {
        float newX = object["x"].get<float>() - centerX;
        float newY = -(object["y"].get<float>() - centerY);

        // 創建物件並設置屬性
        auto unexplored = std::make_shared<Unexplored>("../Resources/Map/TiledProject/Area1_Resources/" + object["name"].get<std::string>() + ".png");
        
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
        
        invisiblewall->SetPosition({newX - respawnpointX - 14, newY - respawnpointY + 14});
        m_Invisiblewalls.push_back(invisiblewall);
    }

    // 遍歷所有物件並調整位置
    for (const auto& object : mapData["layers"][1]["objects"]) {
        float newX = object["x"].get<float>() - centerX;
        float newY = -(object["y"].get<float>() - centerY);

        // 創建物件並設置屬性
        std::shared_ptr<Character> obj;
        if (object["name"].get<std::string>() == "Door") {
            obj = std::make_shared<Door>("../Resources/Map/TiledProject/Area1_Resources/" + object["name"].get<std::string>() + ".png", m_Unexploreds);
            m_Doors.push_back(std::dynamic_pointer_cast<Door>(obj));
        }
        else if (object["name"].get<std::string>() == "CloseChest") {
            obj = std::make_shared<Chest>("../Resources/Map/TiledProject/Area1_Resources/" + object["name"].get<std::string>() + ".png", m_Root);
            m_Chests.push_back(std::dynamic_pointer_cast<Chest>(obj));
        }
        else {
            obj = std::make_shared<Character>("../Resources/Map/TiledProject/Area1_Resources/" + object["name"].get<std::string>() + ".png");
            m_Objects.push_back(obj);
        }

        obj->SetPosition({newX - respawnpointX, newY - respawnpointY + 28});
        obj->SetVisible(true);
        obj->SetZIndex(11);

        m_Root->AddChild(obj);
    }

    // just push box
    m_Box = std::make_shared<Box>("../Resources/Map/Chest/Box.png");
    m_Box->SetVisible(true);
    m_Box->SetZIndex(11);
    m_Box->SetPosition({-28, -28});
    m_Root->AddChild(m_Box);
}

void Map::Update() {
    if (m_CurrentInteracting) {
        m_CurrentInteracting->OnCollision();
    }
}

void Map::Move(glm::vec2 displacement) { 
    for (const auto& invisiblewall : m_Invisiblewalls) {
        if (invisiblewall->IsCollision({invisiblewall->GetPosition().x + displacement.x, invisiblewall->GetPosition().y + displacement.y})) {
            return;
        }
    }
    for (const auto& door : m_Doors) {
        if (door->GetVisibility() && door->IsCollision({door->GetPosition().x + displacement.x, door->GetPosition().y + displacement.y})) {
            m_CurrentInteracting = door;
            return;
        }
    }
    for (const auto& chest : m_Chests) {
        if (chest->IsCollision({chest->GetPosition().x + displacement.x, chest->GetPosition().y + displacement.y})) {
            m_CurrentInteracting = chest;
            return;
        }
    }
    if (m_CurrentInteracting) {
        m_CurrentInteracting->OffCollision();
        m_CurrentInteracting = nullptr;
    }
    
    m_map->SetPosition({m_map->GetPosition().x + displacement.x, m_map->GetPosition().y + displacement.y});
    for (const auto& obj : m_Objects) {
        obj->SetPosition({obj->GetPosition().x + displacement.x, obj->GetPosition().y + displacement.y});
    }
    for (const auto& unexplored : m_Unexploreds) {
        unexplored->SetPosition({unexplored->GetPosition().x + displacement.x, unexplored->GetPosition().y + displacement.y});
    }
    for (const auto& invisiblewall : m_Invisiblewalls) {
        invisiblewall->SetPosition({invisiblewall->GetPosition().x + displacement.x, invisiblewall->GetPosition().y + displacement.y});
    }
    for (const auto& door : m_Doors) {
        door->SetPosition({door->GetPosition().x + displacement.x, door->GetPosition().y + displacement.y});
    }
    for (const auto& chest : m_Chests) {
        chest->SetPosition({chest->GetPosition().x + displacement.x, chest->GetPosition().y + displacement.y});
    }

    //just push box
    if (m_Box->IsCollision({m_Box->GetPosition().x + displacement.x, m_Box->GetPosition().y + displacement.y})) {
        return;
    }
    else {
        m_Box->SetPosition({m_Box->GetPosition().x + displacement.x, m_Box->GetPosition().y + displacement.y});
    }
}