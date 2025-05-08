#ifndef DOOR_HPP
#define DOOR_HPP

#include "pch.hpp"
#include "Character.hpp"
#include "ICollidable.hpp"

class Unexplored;

class Door : public ICollidable, public Character, public std::enable_shared_from_this<Door> {
public:
    Door(const std::string& ImagePath, std::vector<std::shared_ptr<Unexplored>>& unexploreds);

    virtual ~Door() = default;

    bool IsCollision(const std::shared_ptr<Character> &other, glm::vec2 displacement) override;

    void OnCollision() override;

    void OffCollision() override {};

    void ExploreDoorsRecursively(glm::vec2 position);
private:
    std::vector<std::shared_ptr<Unexplored>>& m_Unexploreds;
};

#endif //DOOR_HPP