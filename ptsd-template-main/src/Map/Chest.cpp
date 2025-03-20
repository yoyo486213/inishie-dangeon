#include "Map/Chest.hpp"
#include "Character.hpp"
#include <memory>

Chest::Chest(const std::string& ImagePath, Util::Renderer *m_Root) : Character(ImagePath) {
    std::random_device rd;
    std::mt19937 gen(rd()); // 以隨機設備為種子初始化 Mersenne Twister 引擎
    std::uniform_int_distribution<> dis(50, 100); // 設置範圍 (最小值到最大值)
    
    m_TrapType = TrapType::Fire;

    m_BoxProgressBox = std::make_shared<Character>("../Resources/Map/Chest/Boxprogressbox.png");
    m_BoxProgressBox->SetVisible(false);
    m_BoxProgressBox->SetZIndex(16);
    m_Root->AddChild(m_BoxProgressBox);

    std::vector<std::string> BoxprogressImages;
    BoxprogressImages.reserve(26);
    for (int i = 1; i < 51; i++) {
        char buffer[100];
        snprintf(buffer, sizeof(buffer), "../Resources/Map/Chest/Boxprogress/Boxprogress-%02d.png", i);
        BoxprogressImages.emplace_back(buffer);
    }
    m_BoxProgress = std::make_shared<AnimatedCharacter>(BoxprogressImages);
    m_BoxProgress->SetVisible(false);
    m_BoxProgress->SetLooping(false);
    m_BoxProgress->SetZIndex(17);
    m_BoxProgress->SetInterval(dis(gen));
    m_Root->AddChild(m_BoxProgress);

    std::vector<std::string> TrapImages;
    TrapImages.reserve(26);

    switch (m_TrapType) {
        case TrapType::Fire:
            for (int i = 1; i < 27; i++) {
                char buffer[100];
                snprintf(buffer, sizeof(buffer), "../Resources/Map/Chest/Fire/Fire-%02d.png", i);
                TrapImages.emplace_back(buffer);
            }
            m_TrapAnimation = std::make_shared<AnimatedCharacter>(TrapImages);
            m_TrapBox = std::make_shared<Character>("../Resources/Map/Chest/FireBox.png");
            break;
        case TrapType::Ice:
            for (int i = 0; i < 30; i++) {
                char buffer[100];
                snprintf(buffer, sizeof(buffer), "../Resources/Trap/Map/Chest/Ice/Ice-%02d.png", i);
                TrapImages.emplace_back(buffer);
            }
            m_TrapAnimation = std::make_shared<AnimatedCharacter>(TrapImages);
            break;
        case TrapType::Lightning:
            for (int i = 0; i < 30; i++) {
                char buffer[100];
                snprintf(buffer, sizeof(buffer), "../Resources/Trap/Map/Chest/Lightning/Lightning-%02d.png", i);
                TrapImages.emplace_back(buffer);
            }
            m_TrapAnimation = std::make_shared<AnimatedCharacter>(TrapImages);
            break;
        case TrapType::Explode:
            for (int i = 0; i < 30; i++) {
                char buffer[100];
                snprintf(buffer, sizeof(buffer), "../Resources/Trap/Map/Chest/Explode/Explode-%02d.png", i);
                TrapImages.emplace_back(buffer);
            }
            m_TrapAnimation = std::make_shared<AnimatedCharacter>(TrapImages);
            break;
        case TrapType::Charm:
            for (int i = 0; i < 30; i++) {
                char buffer[100];
                snprintf(buffer, sizeof(buffer), "../Resources/Trap/Map/Chest/Charm/Charm-%02d.png", i);
                TrapImages.emplace_back(buffer);
            }
            m_TrapAnimation = std::make_shared<AnimatedCharacter>(TrapImages);
            break;
        case TrapType::Poison:
            for (int i = 0; i < 30; i++) {
                char buffer[100];
                snprintf(buffer, sizeof(buffer), "../Resources/Trap/Map/Chest/Poison/Poison-%02d.png", i);
                TrapImages.emplace_back(buffer);
            }
            m_TrapAnimation = std::make_shared<AnimatedCharacter>(TrapImages);
            break;
        case TrapType::None:
            break;
        default:
            break;
    }
    if (m_TrapType != TrapType::None) {
        m_TrapBox->SetVisible(false);
        m_TrapBox->SetZIndex(16);
        m_Root->AddChild(m_TrapBox);

        m_TrapAnimation->SetZIndex(17);
        m_TrapAnimation->SetVisible(false);
        m_TrapAnimation->SetLooping(false);
        std::uniform_int_distribution<> dis(20, 100);
        m_TrapAnimation->SetInterval(dis(gen));
        m_Root->AddChild(m_TrapAnimation);
    }
}

bool Chest::IsCollision(glm::vec2 position) {
    float width = 0;
    float height = 0;
    float x = position.x - 14;
    float y = position.y + 14;
    if (x <= width && x + GetScaledSize().x >= -width && y >= -height && y - GetScaledSize().y <= height) {
        return true;
    }
    return false;
}

void Chest::OnCollision() {
    if (opened == false) {
        if (m_TrapType != TrapType::None) {
            m_TrapBox->SetVisible(true);
            m_TrapBox->SetPosition({GetPosition().x, GetPosition().y + 40});

            std::random_device rd;
            std::mt19937 gen(rd()); // 以隨機設備為種子初始化 Mersenne Twister 引擎
            std::uniform_int_distribution<> dis(20, 100); // 設置範圍 (最小值到最大值)
            m_TrapAnimation->SetInterval(dis(gen));
            
            m_TrapAnimation->SetVisible(true);
            m_TrapAnimation->SetPosition({GetPosition().x, GetPosition().y + 40});
            m_TrapAnimation->Play();
        }
        m_BoxProgressBox->SetVisible(true);
        m_BoxProgressBox->SetPosition({GetPosition().x, GetPosition().y + 25});
        m_BoxProgress->SetVisible(true);
        m_BoxProgress->SetPosition({GetPosition().x, GetPosition().y + 25});
        m_BoxProgress->Play();
    }
    
    if (m_BoxProgress->IfAnimationEnds()) {
        opened = true;
        if (m_TrapType != TrapType::None) {
            m_TrapBox->SetVisible(false);
            m_TrapAnimation->SetVisible(false);
        }
        m_BoxProgressBox->SetVisible(false);
        m_BoxProgress->SetVisible(false);
        SetImage("../Resources/Map/TiledProject/Area1_Resources/OpenChest.png");
        // 噴裝備
    }
    if (m_TrapAnimation && m_TrapAnimation->IfAnimationEnds()) {
        opened = true;
        if (m_TrapType != TrapType::None) {
            m_TrapBox->SetVisible(false);
            m_TrapAnimation->SetVisible(false);
        }
        m_BoxProgressBox->SetVisible(false);
        m_BoxProgress->SetVisible(false);
        SetImage("../Resources/Map/TiledProject/Area1_Resources/OpenChest.png");
    }
}

void Chest::OffCollision() {
    if (m_TrapType != TrapType::None) {
        m_TrapBox->SetVisible(false);
        m_TrapAnimation->SetVisible(false);
        m_TrapAnimation->SetCurrentFrame(0);
    }
    m_BoxProgressBox->SetVisible(false);
    m_BoxProgress->SetVisible(false);
    m_BoxProgress->Pause();
}