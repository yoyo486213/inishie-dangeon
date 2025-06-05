#ifndef IUSABLE_HPP
#define IUSABLE_HPP

#include "pch.hpp"

class IUsable {
public:
    virtual bool Use() = 0; //回傳是否被消耗

    virtual ~IUsable() = default;
};

#endif //IUSABLE_HPP