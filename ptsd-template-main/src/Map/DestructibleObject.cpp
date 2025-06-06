#include "Map/DestructibleObject.hpp"

DestructibleObject::DestructibleObject(const std::string &ImagePath) : Character(ImagePath) {}

bool DestructibleObject::IsCollision(const std::shared_ptr<Character> &other, glm::vec2 displacement) {
    glm::vec2 thisSize = this->GetScaledSize();
    glm::vec2 otherSize = other->GetScaledSize();

    glm::vec2 thisPos = this->GetPosition() + displacement - glm::vec2({thisSize.x / 2.0, thisSize.y / 2.0});
    glm::vec2 otherPos = other->GetPosition() - glm::vec2({otherSize.x / 2.0, otherSize.y / 2.0});

    bool xOverlap = thisPos.x + thisSize.x > otherPos.x && otherPos.x + otherSize.x > thisPos.x;
    bool yOverlap = thisPos.y + thisSize.y > otherPos.y && otherPos.y + otherSize.y > thisPos.y;

    return xOverlap && yOverlap && this->GetVisibility() && other->GetVisibility();
}

void DestructibleObject::OnCollision() {
    this->SetVisible(false);
}

void DestructibleObject::OffCollision() {
    //噴裝
}