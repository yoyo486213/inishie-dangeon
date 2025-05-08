#include "Map/Door.hpp"
#include "Map/Unexplored.hpp"

Door::Door(const std::string& ImagePath, std::vector<std::shared_ptr<Unexplored>>& unexploreds) 
    : Character(ImagePath), m_Unexploreds(unexploreds) {}

bool Door::IsCollision(const std::shared_ptr<Character> &other, glm::vec2 displacement) {
    glm::vec2 thisSize = this->GetScaledSize();
    glm::vec2 otherSize = other->GetScaledSize();

    glm::vec2 thisPos = this->GetPosition() + displacement - glm::vec2({thisSize.x / 2.0, thisSize.y / 2.0});
    glm::vec2 otherPos = other->GetPosition() - glm::vec2({otherSize.x / 2.0, otherSize.y / 2.0});

    bool xOverlap = thisPos.x + thisSize.x > otherPos.x && otherPos.x + otherSize.x > thisPos.x;
    bool yOverlap = thisPos.y + thisSize.y > otherPos.y && otherPos.y + otherSize.y > thisPos.y;

    return xOverlap && yOverlap && this->GetVisibility();
}

void Door::OnCollision() {
    if (this->GetVisibility()) {
        ExploreDoorsRecursively(this->GetPosition());
    }
    this->SetVisible(false);
}

void Door::ExploreDoorsRecursively(glm::vec2 position) {
    for (const auto& unexplored : m_Unexploreds) {
        if (unexplored->GetVisibility() && unexplored->IfExplored(position + glm::vec2({0, 28}))) {
            unexplored->SetVisible(false);
            ExploreDoorsRecursively(position + glm::vec2({0, 28}));
        }
        if (unexplored->GetVisibility() && unexplored->IfExplored(position + glm::vec2({0, -28}))) {
            unexplored->SetVisible(false);
            ExploreDoorsRecursively(position + glm::vec2({0, -28}));
        }
        if (unexplored->GetVisibility() && unexplored->IfExplored(position + glm::vec2({28, 0}))) {
            unexplored->SetVisible(false);
            ExploreDoorsRecursively(position + glm::vec2({28, 0}));
        }
        if (unexplored->GetVisibility() && unexplored->IfExplored(position + glm::vec2({-28, 0}))) {
            unexplored->SetVisible(false);
            ExploreDoorsRecursively(position + glm::vec2({-28, 0}));
        }
    }
}