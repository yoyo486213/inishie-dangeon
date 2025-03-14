#ifndef ICLICKABLE_HPP
#define ICLICKABLE_HPP

class IClickable {
public:
    virtual ~IClickable() = default;

    virtual bool IfFocus() = 0;

    virtual bool IfClick() = 0;

    virtual bool IfPressed() { return  false;};
};

#endif //ICLICKABLE_HPP