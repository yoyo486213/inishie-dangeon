#ifndef IUSABLE_HPP
#define IUSABLE_HPP

#include "pch.hpp"

class IUsable {
public:
    virtual void Use() = 0;

    virtual ~IUsable() = default;
};

#endif //IUSABLE_HPP