#include "Map/DownStairs.hpp"
#include "Util/Renderer.hpp"

DownStairs::DownStairs(const std::string& ImagePath, Util::Renderer *m_Root) : Character(ImagePath) {
    std::vector<std::string> TextButtonImages;
    TextButtonImages.reserve(2);
    for (int i = 1; i < 3; i++) {
        char buffer[200];
        snprintf(buffer, sizeof(buffer), RESOURCE_DIR"/Map/DownStairsText/DownStairsText-%d.png", i);
        TextButtonImages.emplace_back(buffer);
    }
    m_TextButton = std::make_shared<Button>(TextButtonImages);
    m_TextButton->SetZIndex(16);
    m_TextButton->SetVisible(false);
    m_Root->AddChild(m_TextButton);
}

bool DownStairs::IsCollision(const std::shared_ptr<Character> &other, glm::vec2 displacement) {
    glm::vec2 thisSize = this->GetScaledSize();
    glm::vec2 otherSize = other->GetScaledSize();

    glm::vec2 thisPos = this->GetPosition() + displacement - glm::vec2({thisSize.x / 2.0, thisSize.y / 2.0});
    glm::vec2 otherPos = other->GetPosition() - glm::vec2({otherSize.x / 2.0, otherSize.y / 2.0});

    bool xOverlap = thisPos.x + thisSize.x > otherPos.x && otherPos.x + otherSize.x > thisPos.x;
    bool yOverlap = thisPos.y + thisSize.y > otherPos.y && otherPos.y + otherSize.y > thisPos.y;

    return xOverlap && yOverlap && this->GetVisibility();
}

void DownStairs::OnCollision() {
    m_TextButton->SetVisible(true);
    m_TextButton->SetPosition(this->GetPosition() + glm::vec2({0, 60}));
}

void DownStairs::OffCollision() {
    m_TextButton->SetVisible(false);
}