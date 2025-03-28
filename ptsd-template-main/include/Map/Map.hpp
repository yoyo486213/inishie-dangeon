#ifndef MAP_HPP
#define MAP_HPP

#include "pch.hpp"
#include "Util/GameObject.hpp"

namespace Util {
    class Renderer;
}
class Character;
class ICollidable;
class InvisibleWall;
class Unexplored;
class Chest;
class Door;
class DownStairs;
class UpStairs;
class DestructibleObject;
class Box;
class Player;
class Monster;

class Map : public Util::GameObject {
public:
    Map(Util::Renderer *m_Root);

    virtual ~Map() = default;

    void Move(glm::vec2 displacement, std::shared_ptr<Player> &m_Player);

    void Update(std::shared_ptr<Player> &m_Player);
private:
    std::shared_ptr<Character> m_map;
    std::vector<std::shared_ptr<DestructibleObject>> m_DestructibleObjects;
    std::shared_ptr<UpStairs> m_UpStairs;
    std::shared_ptr<DownStairs> m_DownStairs;
    std::vector<std::shared_ptr<Door>> m_Doors;
    std::vector<std::shared_ptr<Chest>> m_Chests;
    std::vector<std::shared_ptr<Unexplored>> m_Unexploreds;
    std::vector<std::shared_ptr<InvisibleWall>> m_Invisiblewalls;

    std::vector<std::shared_ptr<ICollidable>> AllCollidableObjects;
    std::vector<std::shared_ptr<Character>> AllObjects; 
    std::shared_ptr<ICollidable> m_CurrentInteracting = nullptr;

    std::vector<std::shared_ptr<Monster>> m_Monsters;
    // just push box
    std::shared_ptr<Box> m_Box;
};

#endif //MAP_HPP