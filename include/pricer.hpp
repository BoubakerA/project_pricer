// pricer.hpp
#ifndef PRICER_HPP
#define PRICER_HPP

#include "option.hpp"

class Pricer {
public:
    virtual ~Pricer() = default;
    virtual double price(const Option& option) const = 0;
};

#endif
