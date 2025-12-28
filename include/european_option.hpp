#ifndef EUROPEAN_OPTION_HPP
#define EUROPEAN_OPTION_HPP

#include "option.hpp"
#include "types.hpp"
#include <algorithm>

class EuropeanOption : public Option {
public:
    EuropeanOption(OptionType type, double S, double K, double r, double v, double T)
        : Option(S, K, r, v, T), type_(type) {}

    bool isPathDependent() const override { return false; }

    double payoff(double ST) const override {
        if (type_ == OptionType::Call)
            return std::max(ST - K_, 0.0);
        else
            return std::max(K_ - ST, 0.0);
    }

    OptionType type() const override { return type_; }

private:
    OptionType type_;
};

#endif
