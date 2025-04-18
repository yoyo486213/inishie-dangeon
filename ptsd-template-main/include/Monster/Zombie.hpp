#ifndef ZOMBIE_HPP
#define ZOMBIE_HPP

#include "pch.hpp"
#include "IMoveable.hpp"
#include "Monster/Monster.hpp"

class Player;
class Character;

class Zombie : public IMoveable, public Monster, public std::enable_shared_from_this<Zombie> {
public:
    enum class State {
        Move,
        MoveMap,
        Stop
    };

    Zombie();

    void Move(glm::vec2 displacement, glm::vec2 goal) override;

    void Update(std::shared_ptr<Player> &m_Player, std::vector<std::shared_ptr<Character>> AllObjects, std::vector<std::shared_ptr<ICollidable>> AllCollidableObjects, std::vector<std::shared_ptr<InvisibleWall>> m_Invisiblewalls, std::vector<std::shared_ptr<Monster>> m_Monsters) override;

    glm::vec2 GetGoalPosition() override { return this->goalpos; }
private:
    State state = State::Stop;
    glm::vec2 randomDisplacement;
    glm::vec2 pos;
    glm::vec2 goalpos;
    int grids;
    int goalgrids;

    bool following = false;
};

#endif //ZOMBIE_HPP