#ifndef PROPS_HPP
#define PROPS_HPP

#include "pch.hpp"
#include "IMoveable.hpp"
#include "ICollidable.hpp"
#include "IClickable.hpp"
#include "Character.hpp"

class Player;

class Props : public ICollidable, public IClickable, public Character, public std::enable_shared_from_this<Props> {
public:
    Props();

    virtual ~Props() = default;

    bool IsCollision(const std::shared_ptr<Character> &other, glm::vec2 displacement) override;

    void OnCollision() override {};
    
    void OffCollision() override {};

    void OnCollision(std::shared_ptr<Player> &m_Player);

    bool IfFocus() override;

    bool IfClick() override { return false; };

    void ChangeImage(int index) { this->SetImage(m_ImagePaths[index - 1]); }
private:
    std::string type;
    std::vector<std::string> m_ImagePaths;
};

#endif //PROPS_HPP