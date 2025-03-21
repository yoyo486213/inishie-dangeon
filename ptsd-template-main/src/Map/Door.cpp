#include "Map/Door.hpp"
#include <memory>

Door::Door(const std::string& ImagePath, std::vector<std::shared_ptr<Unexplored>>& unexploreds) 
    : Character(ImagePath), m_Unexploreds(unexploreds) {}

bool Door::IsCollision(std::shared_ptr<Character> &other, glm::vec2 displacement) {
    glm::vec2 thisPos = this->GetPosition() + displacement;
    glm::vec2 otherPos = other->GetPosition();
    
    glm::vec2 thisSize = this->GetScaledSize();
    glm::vec2 otherSize = other->GetScaledSize();

    bool xOverlap = thisPos.x + thisSize.x > otherPos.x && otherPos.x + otherSize.x > thisPos.x;
    bool yOverlap = thisPos.y + thisSize.y > otherPos.y && otherPos.y + otherSize.y > thisPos.y;

    return xOverlap && yOverlap;
}

void Door::OnCollision() {
    if (this->GetVisibility()) {
        ExploreDoorsRecursively(shared_from_this());
    }
    this->SetVisible(false);
}

void Door::ExploreDoorsRecursively(std::shared_ptr<Door> door) {
    for (const auto& unexplored : m_Unexploreds) {
        if (unexplored->GetVisibility() && unexplored->IfExplored(door->GetPosition())) {
            unexplored->SetVisible(false);
            door->SetPosition({unexplored->GetPosition().x, unexplored->GetPosition().y});
            ExploreDoorsRecursively(door);
        }
    }
}