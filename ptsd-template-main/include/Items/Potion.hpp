#ifndef POTION_HPP
#define POTION_HPP

#include "pch.hpp"
#include "IClickable.hpp"
#include "IUsable.hpp"
#include "Item.hpp"

class Player;
class MyBGM;

class Potion : public IUsable, public IClickable, public Item {
public:
    enum class Type {
        Hp,
        Mp
    };
    
    Potion(std::shared_ptr<Player> &m_Player);

    virtual ~Potion() = default;
    
    bool Use() override;

    bool IfFocus() override;

    bool IfClick() override;

    bool IfPressed() override;
private:
    std::shared_ptr<Player> m_Player;

    Type type;
    std::vector<std::string> m_ImagePaths;
    std::shared_ptr<MyBGM> m_DrinkSFX = std::make_shared<MyBGM>(RESOURCE_DIR"/BGM/sounds/DrinkPotion.wav");
};

#endif //POTION_HPP