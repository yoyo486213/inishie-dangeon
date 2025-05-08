#ifndef BAT_HPP
#define BAT_HPP

#include "pch.hpp"
#include "IMoveable.hpp"
#include "Monster/Monster.hpp"

class Player;
class Character;

class Bat : public Monster, public std::enable_shared_from_this<Bat> {
public:
    Bat();

    void Move(glm::vec2 displacement, glm::vec2 goal, std::vector<std::shared_ptr<Monster>> m_Monsters);

    void Update( std::shared_ptr<Player> &m_Player, std::vector<std::shared_ptr<Character>> AllObjects, std::vector<std::shared_ptr<ICollidable>> AllCollidableObjects, std::vector<std::shared_ptr<InvisibleWall>> m_Invisiblewalls, std::vector<std::shared_ptr<Monster>> m_Monsters) override;
private:
    bool following = false;
};

#endif //Bat_HPP