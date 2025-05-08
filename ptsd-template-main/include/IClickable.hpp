#ifndef ICLICKABLE_HPP
#define ICLICKABLE_HPP

class IClickable {
public:
    virtual ~IClickable() = default;

    virtual bool IfFocus() = 0;

    virtual bool IfClick() = 0;

    virtual bool IfPressed() = 0;
};

#endif //ICLICKABLE_HPP