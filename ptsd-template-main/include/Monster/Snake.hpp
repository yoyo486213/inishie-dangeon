#ifndef SNAKE_HPP
#define SNAKE_HPP

#include "pch.hpp"
#include "IMoveable.hpp"
#include "ICollidable.hpp"
#include "Monster/Monster.hpp"

class Player;
class Character;

class Snake : public IMoveable, public ICollidable, public Monster, public std::enable_shared_from_this<Snake> {
public:
    enum class State {
        Move,
        MoveMap,
        Stop
    };

    Snake();

    void Move(glm::vec2 displacement, glm::vec2 goal) override;

    void Update( std::shared_ptr<Player> &m_Player, std::vector<std::shared_ptr<Character>> AllObjects, std::vector<std::shared_ptr<ICollidable>> AllCollidableObjects, std::vector<std::shared_ptr<InvisibleWall>> m_Invisiblewalls) override;

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

    bool goalchange = true;
    bool throughzero = false;
    glm::vec2 trackpos;
    glm::vec2 trackdisplacement;
};
    
#endif //SNAKE_HPP