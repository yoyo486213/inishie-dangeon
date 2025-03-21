#ifndef MAP_HPP
#define MAP_HPP

#include "pch.hpp"
#include <fstream> 
#include <iostream>
#include <memory>
#include <vector>
#include "Util/GameObject.hpp"
#include "Util/Renderer.hpp"
#include "Character.hpp"
#include "Collidable.hpp"
#include "Map/InvisibleWall.hpp"
#include "Map/Unexplored.hpp"
#include "Map/Chest.hpp"
#include "Map/Door.hpp"
#include "nlohmann/json.hpp"

#include "Map/Box.hpp"

class Map : public Util::GameObject {
public:
    Map(Util::Renderer *m_Root);

    virtual ~Map() = default;

    void Move(glm::vec2 displacement, std::shared_ptr<Character> &m_Butterfly);

    void Update();
private:
    std::shared_ptr<Character> m_map;
    std::vector<std::shared_ptr<Character>> m_Objects;
    std::vector<std::shared_ptr<Door>> m_Doors;
    std::vector<std::shared_ptr<Chest>> m_Chests;
    std::vector<std::shared_ptr<Unexplored>> m_Unexploreds;
    std::vector<std::shared_ptr<InvisibleWall>> m_Invisiblewalls;

    std::shared_ptr<Collidable> m_CurrentInteracting = nullptr;

    // just push box
    std::shared_ptr<Box> m_Box;
};

#endif //MAP_HPP