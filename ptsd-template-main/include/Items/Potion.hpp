#ifndef POTION_HPP
#define POTION_HPP

#include "pch.hpp"
#include "IMoveable.hpp"
#include "IClickable.hpp"
#include "Item.hpp"

class Player;

class Potion : public IClickable, public Item {
public:
    enum class Type {
        Hp,
        Mp
    };
    
    Potion(std::shared_ptr<Player> &m_Player);

    void Use() override;

    virtual ~Potion() = default;

    bool IfFocus() override;

    bool IfClick() override;

    bool IfPressed() override;

    bool useOnSelect() const override { return true; }
private:
    std::shared_ptr<Player> m_Player;

    Type type;
    std::vector<std::string> m_ImagePaths;
};

#endif //POTION_HPP