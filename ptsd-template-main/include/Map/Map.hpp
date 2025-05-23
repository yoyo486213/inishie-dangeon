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
class Potion;
class Orb;
class Weapon;
class Player;
class PlayerUI;
class Monster;

class Map : public Util::GameObject {
public:
    Map(Util::Renderer *m_Root);

    void CreateMap(Util::Renderer *m_Root);

    void CreateItems(glm::vec2 pos, std::shared_ptr<Player> &m_Player, Util::Renderer *m_Root);

    virtual ~Map() = default;

    void Move(glm::vec2 displacement, std::shared_ptr<Player> &m_Player, Util::Renderer *m_Root);

    void Update(std::shared_ptr<Player> &m_Player, std::shared_ptr<PlayerUI> &m_UI, Util::Renderer *m_Root);
private:
    // map
    int floor = 1;
    int beforemapindex = 0;

    std::shared_ptr<Character> m_map;
    std::vector<std::shared_ptr<DestructibleObject>> m_DestructibleObjects;
    std::shared_ptr<UpStairs> m_UpStairs;
    std::shared_ptr<DownStairs> m_DownStairs;
    std::vector<std::shared_ptr<Door>> m_Doors;
    std::vector<std::shared_ptr<Chest>> m_Chests;
    std::vector<std::shared_ptr<Unexplored>> m_Unexploreds;
    std::vector<std::shared_ptr<InvisibleWall>> m_Invisiblewalls;
    
    std::vector<std::shared_ptr<Potion>> m_Potion;
    std::vector<std::shared_ptr<Orb>> m_Orbs;
    std::vector<std::shared_ptr<Weapon>> m_Weapons;

    std::vector<std::shared_ptr<ICollidable>> AllCollidableObjects;
    std::vector<std::shared_ptr<Character>> AllObjects; 
    std::shared_ptr<ICollidable> m_CurrentInteracting = nullptr;

    std::vector<std::shared_ptr<Monster>> m_Monsters;
};

#endif //MAP_HPP