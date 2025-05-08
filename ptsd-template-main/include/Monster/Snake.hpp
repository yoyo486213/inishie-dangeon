#ifndef SNAKE_HPP
#define SNAKE_HPP

#include "pch.hpp"
#include "IMoveable.hpp"
#include "Monster/Monster.hpp"

class Player;
class Character;

class Snake : public Monster, public std::enable_shared_from_this<Snake> {
public:
    Snake();

    void Move(glm::vec2 displacement, glm::vec2 goal, std::vector<std::shared_ptr<Monster>> m_Monsters);

    void Update(std::shared_ptr<Player> &m_Player, std::vector<std::shared_ptr<Character>> AllObjects, std::vector<std::shared_ptr<ICollidable>> AllCollidableObjects, std::vector<std::shared_ptr<InvisibleWall>> m_Invisiblewalls, std::vector<std::shared_ptr<Monster>> m_Monsters) override;
private:
    bool goalchange = true;
    bool throughzero = false;
    glm::vec2 trackpos;
    glm::vec2 trackdisplacement;
};
    
#endif //SNAKE_HPP