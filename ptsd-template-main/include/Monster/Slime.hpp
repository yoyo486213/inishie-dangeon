#ifndef SLIME_HPP
#define SLIME_HPP

#include "pch.hpp"
#include "IMoveable.hpp"
#include "Monster/Monster.hpp"

class Player;
class Character;

class Slime : public IMoveable, public Monster, public std::enable_shared_from_this<Slime> {
public:
    enum class State {
        Move,
        MoveMap,
        Stop
    };

    Slime();

    void Move(glm::vec2 displacement, glm::vec2 goal) override;

    void Update(std::shared_ptr<Player> &m_Player, std::vector<std::shared_ptr<Character>> AllObjects, std::vector<std::shared_ptr<ICollidable>> AllCollidableObjects, std::vector<std::shared_ptr<InvisibleWall>> m_Invisiblewalls, std::vector<std::shared_ptr<Monster>> m_Monsters) override;

    glm::vec2 GetGoalPosition() override { return this->goalpos; }
    
    void SetState(State state) { this->state = state; }

    State GetState() { return state; }
private:
    State state = State::Stop;
    glm::vec2 randomDisplacement;
    glm::vec2 pos;
    glm::vec2 goalpos;
    int grids;
    int goalgrids;

    int walkRateValue = 700;
};

#endif //SLIME_HPP