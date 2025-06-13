#ifndef MAP_HPP
#define MAP_HPP

#include "pch.hpp"
#include "Util/GameObject.hpp"
#include "Character.hpp"
#include "Weapon/Projectile.hpp"
#include "Text.hpp"
#include <memory>

namespace Util {
    class Renderer;
}
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
class Item;
class MyBGM;

class Map : public Util::GameObject, public std::enable_shared_from_this<Map> {
public:
    Map(std::shared_ptr<Player> &m_Player, std::shared_ptr<PlayerUI> &m_UI, Util::Renderer *m_Root);

    void CreateMap(Util::Renderer *m_Root);

    void CreateItems(glm::vec2 pos, std::shared_ptr<Player> &m_Player, Util::Renderer *m_Root);

    void DropItems(glm::vec2 Mouse_pos, std::shared_ptr<Item> Item);

    virtual ~Map() = default;

    void Move(glm::vec2 displacement, std::shared_ptr<Player> &m_Player, Util::Renderer *m_Root);

    void Update(std::shared_ptr<Player> &m_Player, std::shared_ptr<PlayerUI> &m_UI, Util::Renderer *m_Root);

    void AddAllObjects(const std::shared_ptr<Character> &object) {
        AllObjects.push_back(std::dynamic_pointer_cast<Character>(object));
    }

    void AddProjectile(const std::shared_ptr<Projectile> &projectile) {
        m_Projectiles.push_back(projectile);
    }
private:
    // map
    int floor = 1;
    int beforemapindex;
    bool BossSpawned = false;
    std::shared_ptr<Text> m_FloorText;
    std::shared_ptr<Text> m_FloorTensDigits;
    std::shared_ptr<Text> m_FloorSingleDigits;
    std::vector<std::string> FloorImages = {RESOURCE_DIR"/Text/BigLetter/B.png", RESOURCE_DIR"/Text/Number/1.png",
                                            RESOURCE_DIR"/Text/Number/2.png", RESOURCE_DIR"/Text/Number/3.png",
                                            RESOURCE_DIR"/Text/Number/4.png", RESOURCE_DIR"/Text/Number/5.png", 
                                            RESOURCE_DIR"/Text/Number/6.png", RESOURCE_DIR"/Text/Number/7.png",
                                            RESOURCE_DIR"/Text/Number/8.png", RESOURCE_DIR"/Text/Number/9.png"};

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

    std::vector<std::shared_ptr<Projectile>> m_Projectiles;

    
    std::shared_ptr<MyBGM> m_StairsSFX;
    std::shared_ptr<MyBGM> m_ChestSFX;
    std::shared_ptr<MyBGM> m_ItemDropSFX = std::make_shared<MyBGM>(RESOURCE_DIR"/BGM/sounds/ItemDrop.wav");
    std::shared_ptr<MyBGM> m_BossSFX = std::make_shared<MyBGM>(RESOURCE_DIR"/BGM/sounds/BOSS.wav");
};

#endif //MAP_HPP