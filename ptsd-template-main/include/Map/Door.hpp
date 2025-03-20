#ifndef DOOR_HPP
#define DOOR_HPP

#include "pch.hpp"
#include "Character.hpp"
#include "Collidable.hpp"
#include "Map/Unexplored.hpp"

class Door : public Collidable, public Character, public std::enable_shared_from_this<Door> {
public:
    Door(const std::string& ImagePath, std::vector<std::shared_ptr<Unexplored>>& unexploreds);

    virtual ~Door() = default;

    bool IsCollision(glm::vec2 position) override;

    void OnCollision() override;

    void OffCollision() override {};

    void ExploreDoorsRecursively(std::shared_ptr<Door> door);
private:
    std::vector<std::shared_ptr<Unexplored>>& m_Unexploreds;
};

#endif //DOOR_HPP