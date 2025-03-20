#include "Map/Door.hpp"
#include <memory>

Door::Door(const std::string& ImagePath, std::vector<std::shared_ptr<Unexplored>>& unexploreds) 
    : Character(ImagePath), m_Unexploreds(unexploreds) {}

bool Door::IsCollision(glm::vec2 position) {
    float width = 0;
    float hight = 0;
    float x = position.x - 14;
    float y = position.y + 14;
    if (x <= width && x + GetScaledSize().x >= -width && y >= -hight && y - GetScaledSize().y <= hight) {
        return true;
    }
    return false;
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