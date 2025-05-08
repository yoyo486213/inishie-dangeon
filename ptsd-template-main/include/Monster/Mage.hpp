#ifndef MAGE_HPP
#define MAGE_HPP

#include "pch.hpp"
#include "IMoveable.hpp"
#include "Monster/Monster.hpp"

class Player;
class Character;

class Mage : public Monster, public std::enable_shared_from_this<Mage> {
public:
    Mage();

    void Move(glm::vec2 displacement, glm::vec2 goal, std::vector<std::shared_ptr<Monster>> m_Monsters);

    void Update(std::shared_ptr<Player> &m_Player, std::vector<std::shared_ptr<Character>> AllObjects, std::vector<std::shared_ptr<ICollidable>> AllCollidableObjects, std::vector<std::shared_ptr<InvisibleWall>> m_Invisiblewalls, std::vector<std::shared_ptr<Monster>> m_Monsters) override;
};

#endif //MAGE_HPP