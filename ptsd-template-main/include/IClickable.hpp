#ifndef ICLICKABLE_HPP
#define ICLICKABLE_HPP

class IClickable {
public:
    virtual bool IfFocus() = 0;

    virtual bool IfClick() = 0;

    virtual ~IClickable() = default;
};

#endif //ICLICKABLE_HPP