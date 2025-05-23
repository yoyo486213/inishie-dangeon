#include "Map/Unexplored.hpp"

Unexplored::Unexplored(const std::string& ImagePath) : Character(ImagePath){}

bool Unexplored::IfExplored(glm::vec2 position) {
    // 精確比較兩個中心點是否相同
    return glm::distance(position, GetPosition()) < 0.1f; // 加一點誤差保險
}
