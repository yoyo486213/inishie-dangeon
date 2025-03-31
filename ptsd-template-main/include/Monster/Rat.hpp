#ifndef RAT_HPP
#define RAT_HPP

#include "pch.hpp"
#include "IMoveable.hpp"
#include "ICollidable.hpp"
#include "Monster/Monster.hpp"

class Player;
class Character;

class Rat : public IMoveable, public ICollidable, public Monster, public std::enable_shared_from_this<Rat> {
public:
    enum class State {
        Move,
        MoveMap,
        Attack,
        Stop
    };

    Rat();

    void Move(glm::vec2 displacement, glm::vec2 goal) override;

    int Attack() override;

    void Update( std::shared_ptr<Player> &m_Player, std::vector<std::shared_ptr<Character>> AllObjects, std::vector<std::shared_ptr<ICollidable>> AllCollidableObjects, std::vector<std::shared_ptr<InvisibleWall>> m_Invisiblewalls) override;

    void SetState(State state) { this->state = state; }

    State GetState() { return state; }

    bool IsCollision(const std::shared_ptr<Character> &other, glm::vec2 displacement) override;

    void OnCollision() override {};

    void OffCollision() override {};
private:
    State state = State::Stop;
    glm::vec2 randomDisplacement;
    glm::vec2 pos;
    glm::vec2 goalpos;
    int grids;
    int goalgrids;
};

#endif //RAT_HPP