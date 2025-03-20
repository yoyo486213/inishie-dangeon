#include "Map/Box.hpp"

Box::Box(const std::string& ImagePath) : Character(ImagePath) {}

bool Box::IsCollision(Character& other) {
    // 獲取物件的座標與大小
    glm::vec2 thisPos = this->GetPosition(); // 假設有個方法可以獲取 Box 的位置
    glm::vec2 otherPos = other.GetPosition();
    
    glm::vec2 thisSize = this->GetScaledSize();
    glm::vec2 otherSize = other.GetScaledSize();

    // 檢查兩物件是否有重疊
    bool xOverlap = thisPos.x + thisSize.x > otherPos.x && otherPos.x + otherSize.x > thisPos.x;
    bool yOverlap = thisPos.y + thisSize.y > otherPos.y && otherPos.y + otherSize.y > thisPos.y;

    return xOverlap && yOverlap;
}
