#ifndef DIGITAL_OPTION_HPP
#define DIGITAL_OPTION_HPP  

#include "option.hpp"
#include "types.hpp"
#include <algorithm>

class DigitalOption : public Option {
public:

DigitalOption(OptionType type, double S, double K, double r, double v, double T, double cashPayoff = 1.0)
        : Option(S, K, r, v, T), type_(type), K_(K), T_(T), cash_(cashPayoff) {}

    bool isPathDependent() const override { return false; }

    double payoff(double ST) const override {
        if (type_ == OptionType::Call)
            return (ST > K_) ? cash_ : 0.0;
        else
            return (ST < K_) ? cash_ : 0.0;
    }

    OptionType type() const { return type_; }
    double strike() const { return K_; }
    double cash() const { return cash_; }

private:
    OptionType type_;
    double K_, T_, cash_;
};

#endif