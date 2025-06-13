#ifndef ORB_HPP
#define ORB_HPP

#include "pch.hpp"
#include "Character.hpp"
#include "ICollidable.hpp"
#include "IClickable.hpp"

class Player;
class MyBGM;

class Orb : public IClickable, public ICollidable, public Character {
public:
    enum class Type {
        Hp,
        Mp
    };

    Orb(std::shared_ptr<Player> m_Player);
    
    virtual ~Orb() = default;

    bool IsCollision(const std::shared_ptr<Character> &other, glm::vec2 displacement) override;

    void OnCollision() override {};

    void OnCollision(std::shared_ptr<Player> &m_Player);

    void OffCollision() override {};

    bool IfFocus() override;

    bool IfClick() override;

    bool IfPressed() override;

    void ChangeImage(int index) {
        this->SetImage(this->ImagePaths[index - 1]);
    }
private:
    std::shared_ptr<Player> m_Player;

    Type type;
    std::vector<std::string> ImagePaths;
    std::shared_ptr<MyBGM> m_DrinkSFX = std::make_shared<MyBGM>(RESOURCE_DIR"/BGM/sounds/DrinkPotion.wav");
};

#endif // ORB_HPP