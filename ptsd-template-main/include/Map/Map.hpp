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
    Map(Util::Renderer *m_Root);
    
    void Update();

    void Move(glm::vec2 displacement);
private:
    std::shared_ptr<Character> m_map;
    std::vector<std::shared_ptr<Character>> m_Objects;
    std::vector<std::shared_ptr<InvisibleWall>> m_Invisiblewalls;
};

#endif //MAP_HPP